#include "SettingsState.hpp"

SettingsState::SettingsState(ah::StateManager& manager)
: ah::State(manager,lp::type<SettingsState>())
{
    mKeySelected = 0;

    sf::Vector2u wSize = ah::Application::getWindow().getSize();
    sf::Vector2f scale = sf::Vector2f(wSize.x/800.f,wSize.y/600.f);

    sf::Vector2f bSize = sf::Vector2f(400 * scale.x, 75 * scale.y);

    mWindow = sfg::Window::Create(sfg::Window::BACKGROUND);
    auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.f);

    //Begin Audio
    mGlobalL = sfg::Label::Create(std::to_string(static_cast<int>(ah::Application::getAudio().getGlobalVolume())));
    mGlobalS = sfg::Scale::Create(0.f,100.f,1.f,sfg::Range::Orientation::HORIZONTAL);
    mGlobalS->SetValue(ah::Application::getAudio().getGlobalVolume());
    mGlobalS->GetAdjustment()->GetSignal(sfg::Adjustment::OnChange).Connect([&]()
    {
        float v = mGlobalS->GetValue();
        mGlobalL->SetText(std::to_string(static_cast<int>(v)));
        ah::Application::getAudio().setGlobalVolume(v);
    });
    auto h1 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.f);
    h1->Pack(sfg::Label::Create("Global Volume"));
    h1->Pack(mGlobalS);
    h1->Pack(mGlobalL);

    mMusicL = sfg::Label::Create(std::to_string(static_cast<int>(ah::Application::getAudio().getMusicVolume())));
    mMusicS = sfg::Scale::Create(0.f,100.f,1.f,sfg::Range::Orientation::HORIZONTAL);
    mMusicS->SetValue(ah::Application::getAudio().getMusicVolume());
    mMusicS->GetAdjustment()->GetSignal(sfg::Adjustment::OnChange).Connect([&]()
    {
        float v = mMusicS->GetValue();
        mMusicL->SetText(std::to_string(static_cast<int>(v)));
        ah::Application::getAudio().setMusicVolume(v);
    });
    auto h2 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.f);
    h2->Pack(sfg::Label::Create("Music Volume"));
    h2->Pack(mMusicS);
    h2->Pack(mMusicL);

    mSoundL = sfg::Label::Create(std::to_string(static_cast<int>(ah::Application::getAudio().getSoundVolume())));
    mSoundS = sfg::Scale::Create(0.f,100.f,1.f,sfg::Range::Orientation::HORIZONTAL);
    mSoundS->SetValue(ah::Application::getAudio().getSoundVolume());
    mSoundS->GetAdjustment()->GetSignal(sfg::Adjustment::OnChange).Connect([&]()
    {
        float v = mSoundS->GetValue();
        mSoundL->SetText(std::to_string(static_cast<int>(v)));
        ah::Application::getAudio().setSoundVolume(v);
    });
    auto h3 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.f);
    h3->Pack(sfg::Label::Create("Sound Volume"));
    h3->Pack(mSoundS);
    h3->Pack(mSoundL);

    auto a = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.f);
    a->Pack(h1);
    a->Pack(h2);
    a->Pack(h3);

    auto frameA = sfg::Frame::Create("Audio");
    frameA->Add(a);
    frameA->SetAlignment(sf::Vector2f(0.1f,0.f));

    box->Pack(frameA);
    //End Audio

    // Begin Graphics
    mRes = sfg::ComboBox::Create();
    auto res = sf::VideoMode::getFullscreenModes();
    for (std::size_t i = 0; i < res.size(); i++)
    {
        sf::Vector2u s = sf::Vector2u(res[i].width,res[i].height);
        if (s.x != wSize.x && s.y != wSize.y)
        {
            mRes->AppendItem(std::to_string(s.x) + "x" + std::to_string(s.y));
        }
    }
    mRes->PrependItem(std::to_string(wSize.x) + "x" + std::to_string(wSize.y));
    mRes->SelectItem(0);
    mRes->GetSignal(sfg::ComboBox::OnSelect).Connect([&]()
    {
        std::string s = static_cast<std::string>(mRes->GetSelectedText());
        std::string w = s.substr(0,s.find("x"));
        std::string h = s.substr(s.find("x")+1);
        ah::Application::getWindow().setVideoMode(sf::VideoMode(std::stoi(w),std::stoi(h)));
        sf::Vector2u ws = ah::Application::getWindow().getSize();
        mWindow->Refresh();
        mWindow->SetPosition(sf::Vector2f(ws.x / 2.f - mWindow->GetAllocation().width / 2.f, ws.y / 2.f - mWindow->GetAllocation().height / 2.f));
    });

    auto h4 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.f);
    h4->Pack(sfg::Label::Create("VideoMode"));
    h4->Pack(mRes);

    mVerticalSync = sfg::CheckButton::Create("VerticalSync");
    mVerticalSync->SetActive(ah::Application::getWindow().isVerticalSyncEnabled());
    mVerticalSync->GetSignal(sfg::Widget::OnLeftClick).Connect([&]()
    {
        ah::Application::getWindow().setVerticalSyncEnabled(mVerticalSync->IsActive());
    });
    auto h5 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.f);
    h5->Pack(mVerticalSync);

    mFullscreen = sfg::CheckButton::Create("Fullscreen");
    mFullscreen->SetActive(ah::Application::getWindow().isFullscreen());
    mFullscreen->GetSignal(sfg::Widget::OnLeftClick).Connect([&]()
    {
        ah::Application::getWindow().setFullscreen(mFullscreen->IsActive());
    });
    auto h6 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.f);
    h6->Pack(mFullscreen);

    auto b = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.f);
    b->Pack(h4);
    b->Pack(h5);
    b->Pack(h6);

    auto frameG = sfg::Frame::Create("Graphics");
    frameG->Add(b);
    frameG->SetAlignment(sf::Vector2f(0.1f,0.f));

    box->Pack(frameG);
    // End Graphics

    // Begin Key Binding
    mKeyLeft = sfg::Button::Create(thor::toString(ah::Application::getBinding().getKey("left")));
    mKeyLeft->GetSignal(sfg::Widget::OnLeftClick).Connect([&]()
    {
        mKeySelected = 1;
    });
    auto h7 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.f);
    h7->Pack(sfg::Label::Create("Left"));
    h7->Pack(mKeyLeft);

    mKeyRight = sfg::Button::Create(thor::toString(ah::Application::getBinding().getKey("right")));
    mKeyRight->GetSignal(sfg::Widget::OnLeftClick).Connect([&]()
    {
        mKeySelected = 2;
    });
    auto h8 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.f);
    h8->Pack(sfg::Label::Create("Right"));
    h8->Pack(mKeyRight);

    auto c = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.f);
    c->Pack(h7);
    c->Pack(h8);

    auto frameB = sfg::Frame::Create("Key Binding");
    frameB->Add(c);
    frameB->SetAlignment(sf::Vector2f(0.1f,0.f));

    box->Pack(frameB);
    // End Key Binding


    // Begin Game Settings

    // WRITE GAME SETTINGS GUI HERE
    auto d = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.f);
    //d->Pack(...);
    //d->Pack(...);

    auto frameS = sfg::Frame::Create("Game Settings");
    frameS->Add(d);
    frameS->SetAlignment(sf::Vector2f(0.1f,0.f));

    box->Pack(frameS);

    // End Game Settings

    auto buttonQuit = sfg::Button::Create("Return");
	buttonQuit->SetClass("menu_button");
	buttonQuit->SetAllocation(sf::FloatRect(wSize.x / 2 - bSize.x * 0.5f, 450.f * scale.y, bSize.x, bSize.y));
	buttonQuit->GetSignal(sfg::Widget::OnLeftClick).Connect([&]()
    {
        requestClear();
        requestPush(lp::type<MenuState>());
    });

    box->Pack(buttonQuit);

    mWindow->Add(box);
    mWindow->SetPosition(sf::Vector2f(wSize.x / 2.f - mWindow->GetAllocation().width / 2.f, wSize.y / 2.f - mWindow->GetAllocation().height / 2.f));

	mDesktop.Add(mWindow);
}

SettingsState::~SettingsState()
{
}

bool SettingsState::handleEvent(sf::Event const& event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        mKeySelected = 0;
    }
    if (event.type == sf::Event::KeyPressed && mKeySelected != 0)
    {
        switch (mKeySelected)
        {
            case 1:
            {
                ah::Application::getBinding().setKey("left",event.key.code);
                mKeyLeft->SetLabel(thor::toString(event.key.code));
            } break;

            case 2:
            {
                ah::Application::getBinding().setKey("right",event.key.code);
                mKeyRight->SetLabel(thor::toString(event.key.code));
            } break;

            default: break;
        }
    }

    mDesktop.HandleEvent(event);
    return true;
}

bool SettingsState::update(sf::Time dt)
{
    mDesktop.Update(dt.asSeconds());
    return true;
}

void SettingsState::render(sf::RenderTarget& target, sf::RenderStates states)
{
    states.transform *= getTransform();
    mSfgui.Display(ah::Application::getWindow());
}

void SettingsState::onActivate()
{
}

void SettingsState::onDeactivate()
{
}
