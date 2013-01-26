#include "PhoenixEngine.h"
#include "Utility.h"
#include <iostream>
#include <ctime>
#include <typeinfo>

static const float VERSION = 1.0f;
static const float SUB_VERSION = 0.0f;

PhoenixEngine PhoenixEngine::m_Instance;
GameState* PhoenixEngine::m_QueuedState;
bool PhoenixEngine::bLoading;
sf::Time PhoenixEngine::DeltaTime;

PhoenixEngine::PhoenixEngine() : m_AsyncThread(&AsyncDraw)
{
	/* Defaults */
	srand(time(NULL));
	VID_FLAGS = sf::Style::Default;
	DESIRED_FPS = 60;
	RESOLUTION = sf::Vector2u(800, 600);
	WINDOW_TITLE = "Phoenix Engine";
	bVSYNC = false;
	DeltaTime = sf::milliseconds(0);

	m_CurrentState = nullptr;
	m_QueuedState = nullptr;
	m_LoadingState = nullptr;
}

PhoenixEngine::~PhoenixEngine()
{
	if(m_CurrentState != nullptr)
		delete m_CurrentState;
	if(m_QueuedState != nullptr)
		delete m_QueuedState;
	if(m_LoadingState != nullptr)
		delete m_LoadingState;
}

void PhoenixEngine::Init()
{
	/* ASCII art + Version print */
	std::vector<std::string> ASCII_Sequence;
	std::vector<CON_COLOR> Color_Sequence;
	ASCII_Sequence.push_back("______  _                          _         _____                _              ");
	ASCII_Sequence.push_back("| ___ \\| |                        (_)       |  ___|              (_)             ");
	ASCII_Sequence.push_back("| |_/ /| |__    ___    ___  _ __   _ __  __ | |__   _ __    __ _  _  _ __    ___ ");
	ASCII_Sequence.push_back("|  __/ | '_ \\  / _ \\  / _ \\| '_ \\ | |\\ \\/ / |  __| | '_ \\  / _` || || '_ \\  / _ \\");
	ASCII_Sequence.push_back("| |    | | | || (_) ||  __/| | | || | >  <  | |___ | | | || (_| || || | | ||  __/");
	ASCII_Sequence.push_back("\\_|    |_| |_| \\___/  \\___||_| |_||_|/_/\\_\\ \\____/ |_| |_| \\__, ||_||_| |_| \\___|");
	ASCII_Sequence.push_back("                                                            __/ |                ");
	ASCII_Sequence.push_back("                                                           |___/                 ");
	Color_Sequence.push_back(LIGHTYELLOW);
	Color_Sequence.push_back(LIGHTYELLOW);
	Color_Sequence.push_back(LIGHTYELLOW);
	Color_Sequence.push_back(LIGHTRED);
	Color_Sequence.push_back(LIGHTRED);
	Color_Sequence.push_back(RED);
	Color_Sequence.push_back(RED);
	Color_Sequence.push_back(RED);

	for(unsigned int i = 0; i < ASCII_Sequence.size(); i++)
		Util::PrintColor(Util::BuildString("%s\n", ASCII_Sequence[i].c_str()), Color_Sequence[i]);
	Util::PrintColor("Phoenix Engine [ ", RED);
	Util::PrintColor(Util::BuildString("version %1.1f.%1.1f", VERSION, SUB_VERSION), LIGHTRED);
	Util::PrintColor(" ]\n\n\n", RED);

	/* System init */
	Util::msgStd("Starting Phoenix Engine...");

	m_DisplayWindow.create(sf::VideoMode(RESOLUTION.x, RESOLUTION.y), WINDOW_TITLE, VID_FLAGS);

	if(!bVSYNC)
		m_DisplayWindow.setFramerateLimit(DESIRED_FPS);
	else
		m_DisplayWindow.setVerticalSyncEnabled(true);

	if(m_LoadingState != nullptr)
		m_LoadingState->Init();
	else
		Util::msgWarn("No LoadingState set; Screen will be black while loading.");
}

void PhoenixEngine::ChangeState()
{
	if(m_QueuedState == m_LoadingState)
	{
		m_CurrentState = m_LoadingState;
		return;
	}

	if(m_QueuedState != nullptr)
	{
		if(m_CurrentState != nullptr)
		{
			delete m_CurrentState;
			m_CurrentState = nullptr;
		}

		GameState* TemporaryState = m_QueuedState;
		ToggleLoading(true);
		TemporaryState->Init();
		ToggleLoading(false);
		m_CurrentState = TemporaryState;

		Util::msgNote(Util::BuildString("State Loaded: %s", typeid(*m_CurrentState).name()));

		m_QueuedState = nullptr;
	}
}

void PhoenixEngine::ToggleLoading(bool bToggle)
{
	if(m_LoadingState != nullptr)
	{
		if(bToggle)
		{
			bLoading = true;
			m_QueuedState = m_LoadingState;
			ChangeState();
			m_DisplayWindow.setActive(false); //Give thread access to window context
			m_AsyncThread.launch();
		}
		else
		{
			bLoading = false;
			m_AsyncThread.wait();
			m_DisplayWindow.setActive(true);
		}
	}
}

void PhoenixEngine::Update()
{
	DeltaTime = m_DeltaTimer.restart();

	if(m_QueuedState != nullptr)
		ChangeState();

	while(m_DisplayWindow.pollEvent(EventHandle))
	{
		if (EventHandle.type == sf::Event::Closed)
			Quit();

		if(m_CurrentState != nullptr)
			m_CurrentState->HandleEvents(EventHandle);
	}

	if(m_CurrentState != nullptr)
		m_CurrentState->Update(DeltaTime);
}

void PhoenixEngine::Draw()
{
	m_DisplayWindow.clear();

	if(m_CurrentState != nullptr)
		m_CurrentState->Draw(&m_DisplayWindow);

	m_DisplayWindow.display();
}

void PhoenixEngine::AsyncDraw()
{
	while(PhoenixEngine::GetInstance()->Loading())
	{
		PhoenixEngine::GetInstance()->Update();
		PhoenixEngine::GetInstance()->Draw();
	}
}