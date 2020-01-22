//
//#include "InputManager.h"
//#include <iostream>
//
//InputManagerC::InputManagerC()
//{
//
//}
//
//
//InputManagerC::~InputManagerC()
//{
//
//}
//
//void InputManagerC::AddListener(EventListener::Event evt,EventListener *listener)
//{
//	//if (listeners.find(evt) == listeners.end()) { //event not in map add it.
//	//	listeners[evt] = new std::vector<EventListener*>();
//	//}
//
//	//listeners[evt]->push_back(listener);
//
//	////buttonSpace_ = new JumpCommand();
//
//}
//
////Send the events to interested objects
//void InputManagerC::Dispatch(EventListener::Event evt)
//{
//
//	//if (listeners.find(evt) != listeners.end()) {
//
//	//	for (auto const &listener : *listeners[evt]) { //go through all listeners for this event
//	//		listener->onEvent(evt); //Call on event for the listener
//	//	}
//	//}
//}

//Gnereate events
//void InputManagerC::ProcessInput()
//{
//	SDL_Event e;
//	while (SDL_PollEvent(&e) != 0)
//	{
//		switch (e.type) {
//
//		case SDL_KEYDOWN:
//			switch (e.key.keysym.sym) {
//			case SDLK_SPACE:
//				StickLeft->execute();
//				//commander->commands.push_back(buttonSpace_);
//				//Dispatch(EventListener::Event::SPACE);
//				break;
//			case SDLK_a:
//				buttonA_->execute();
//				//commander->commands.push_back(buttonA_);
//				//Dispatch(EventListener::Event::LEFT);
//				break;
//			case SDLK_s:
//				buttonS_->execute();
//				//commander->commands.push_back(buttonS_);
//			//	Dispatch(EventListener::Event::DOWN);
//				break;
//			case SDLK_d:
//				buttonD_->execute();
//				//commander->commands.push_back(buttonD_);
//				//Dispatch(EventListener::Event::RIGHT);
//				break;
//			case SDLK_w:
//				buttonW_->execute();
//				//commander->commands.push_back(buttonW_);
//				//Dispatch(EventListener::Event::UP);
//				break;
//			case SDLK_BACKSPACE:
//			//	buttonBS_->execute();
//				//commander->commands.push_back(buttonW_);
//				for (int i = commander->commands.size(); i > 1; i--)
//				{
//					if (commander->commands[i-1] == buttonSpace_)
//					{
//						std::cout << "Undoing Command : Jump" << std::endl;
//					}
//					else if (commander->commands[i-1] == buttonS_)
//					{
//						std::cout << "Undoing Command : Move Down" << std::endl;
//					}
//					else if (commander->commands[i-1] == buttonA_)
//					{
//						std::cout << "Undoing Command : Move Left" << std::endl;
//					}
//					else if (commander->commands[i-1] == buttonD_)
//					{
//						std::cout << "Undoing Command : Move Right" << std::endl;
//					}
//					else if (commander->commands[i-1] == buttonW_)
//					{
//						std::cout << "Undoing Command : Move Up" << std::endl;
//					}
//					commander->commands.pop_back();
//					break;
//				}
//				//Dispatch(EventListener::Event::UNDO);
//				break;
//			}
//			break;
//		}
//	}
//	//check for exit
//}
