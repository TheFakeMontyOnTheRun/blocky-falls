#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <algorithm>

#include "CLevel.h"
#include "IRenderer.h"
#include "CGame.h"

#include <SDL/SDL.h>
#include <map>

#include "CSDLRenderer.h"


namespace BlockyFalls {
	CGame::CGame() {
		this->mLevel = std::make_shared<CLevel>();
	}

	void CGame::update() {
		this->mRenderer->update();
	}
	
	std::shared_ptr<CLevel> CGame::getLevel() {
		return this->mLevel;
	}
	
	void CGame::runGame( std::shared_ptr<IRenderer> render ){
		this->mRenderer = render;	
		

		auto nr = dynamic_cast<CSDLRenderer*>(render.get());
		nr->setLevel( this->mLevel );
		
	}
}
