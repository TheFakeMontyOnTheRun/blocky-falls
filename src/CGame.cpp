#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <algorithm>

#include "CLevel.h"
#include "IRenderer.h"
#include "CGame.h"

namespace BlockyFalls {
	CGame::CGame() {
	}

	void CGame::update() {
		this->mRenderer->update();
	}
	
	void CGame::runGame( std::shared_ptr<IRenderer> render ){
		this->mRenderer = render;	
	}
}
