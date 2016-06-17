#include <algorithm>
#include <random>
#include <utility>

#include "Vipper/Vipper.h"
#include "Modules/Gameplay/Entities/CColumn.h"

namespace BlockyFalls {

    CColumn::CColumn() { 
      for ( int y = 0; y < kColumnHeight; ++y ) {
          mBlocks.push_back( getRandomPiece() );
      }
    }
    
    CColumn::EColour CColumn::colourAt( int index ) {  
      if ( index < 0 || index >= mBlocks.size() ) {
        return CColumn::EColour::eNothing;
      }
      
      return mBlocks[ index ];
    }

    std::pair<int, int> transformPosition( std::pair<int, int> pos ) {
        return std::pair<int, int>( pos.first, CColumn::kColumnHeight - pos.second - 1);
    }
    
    std::vector<std::tuple<std::pair<int,int>, std::pair<int, int>, CColumn::EColour>> CColumn::getDropList(int xPos) {
        
        std::vector<std::tuple<std::pair<int,int>, std::pair<int, int>, CColumn::EColour>> toReturn;
        size_t size = mBlocks.size();
        int solidBlocks = 0;
        int emptyBlocks = 0;
        int position = 0;
        for ( auto& block : mBlocks ) {

            if ( block == CColumn::EColour::eNothing ) {
                emptyBlocks++;
            } else {
                if ( emptyBlocks > 0 ) {
                    auto from = transformPosition( std::pair<int,int>( xPos, position ) );
                    auto to = transformPosition( std::pair<int, int>(xPos, solidBlocks ) );
                    auto path = std::tuple< std::pair<int,int>, std::pair<int, int>, CColumn::EColour >( from, to, block );
                    toReturn.push_back(  path );
                }
                solidBlocks++;                
            }

            ++position;            
        }
        return toReturn;
    }

    void CColumn::dropBlocksAboveEmptySpaces() {
        mBlocks.erase( std::remove( mBlocks.begin(), mBlocks.end(), EColour::eNothing ), mBlocks.end() );
    }


    
    bool CColumn::isEmpty() {
        for ( auto& brick : mBlocks ) {
            if ( brick != EColour::eNothing ) {
                return false;
            }
        }
        
        return true;
    }
    
    void CColumn::breakBlockAt( int index ) {
        if ( index >= mBlocks.size() || index < 0) {
            return;
        }
        
        mBlocks[ index] = EColour::eNothing;
    }
    
    CColumn::EColour CColumn::getRandomPiece() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(0, 3);
        
        enum class EColour{ eRed, eYellow, eGrey, eBlue, eNothing};
        
        static CColumn::EColour values[]{ CColumn::EColour::eRed, CColumn::EColour::eYellow, CColumn::EColour::eGrey, CColumn::EColour::eBlue};

        return values[ dis(gen) ];
    }
}

