#include <iostream>
#include <algorithm>
#include <random>

#include "Vipper/Vipper.h"
#include "Modules/Gameplay/Entities/CColumn.h"
#include "Modules/Gameplay/Entities/CLevel.h"

namespace BlockyFalls {
  
    void CLevel::addRandomColumn() {
        
        auto column = std::make_shared<CColumn>();
        mColumns.insert( mColumns.begin(), column );
    }
  
    CLevel::CLevel( int initialColumns ) {
        for ( int x = 0; x <= initialColumns; ++x ) {
            addRandomColumn();
        }
    }
    
    
    
    CColumn::EColour CLevel::colourAt( int x, int y ) {
      
        if ( x >= 0 && x < mColumns.size() ) {
            auto column = mColumns[ x ];
      
            if ( y >= 0 && y < CColumn::kColumnHeight ) {
                return column->colourAt( y );
            }
        }
      
        return CColumn::EColour::eNothing;
    }
    
    
    
    
    
    
    
    
    bool CLevel::canBreakAt( int x, int y ) {
        return colourAt( x, y )  != CColumn::EColour::eNothing && ( 
            colourAt( x, y ) == colourAt( x + 1, y) ||
            colourAt( x, y ) == colourAt( x - 1, y) ||
            colourAt( x, y ) == colourAt( x, y + 1) ||
            colourAt( x, y ) == colourAt( x, y - 1)
        );
    }
    
    void CLevel::propagate( int x, int y ) {
        
        if ( x >= mColumns.size() || x < 0 ) {
            return;
        }
        
        if ( y >= CColumn::kColumnHeight || y < 0 ) {
            return;
        }
        
        auto originalColour = colourAt( x, y ); 
        
        if ( originalColour == CColumn::EColour::eNothing ) {
            return;
        } 
                
        mColumns[ x ]->breakBlockAt( y );
        
        if ( originalColour == colourAt( x + 1, y) ) {
            propagate( x + 1, y );        
        }
            
        if ( originalColour == colourAt( x - 1, y) ) {
            propagate( x - 1, y );
        }
            
        if ( originalColour == colourAt( x, y + 1) ) {
            propagate( x, y + 1);    
        }
            
        if ( originalColour == colourAt( x, y - 1)  ) {
            propagate( x, y - 1);
        }
    }
    
    
    void CLevel::breakBlockAt( std::pair<int, int> position ) {        
        int x = position.first;
        int y = position.second;
        auto colour = colourAt( x, y );
        
        if ( canBreakAt( x, y ) ) {
            propagate( x, y );
        }
        
        collapseEmptyColumns();
        dropBlocksAboveEmptySpaces();
    }
    
    void CLevel::collapseEmptyColumns() {     
        static const auto predicate = [](std::shared_ptr<CColumn> c) {
            return c->isEmpty();
        };
        
        mColumns.erase( std::remove_if( mColumns.begin(), mColumns.end(), predicate), mColumns.end() );
    }
    
    void CLevel::dropBlocksAboveEmptySpaces() {
        for ( auto& column : mColumns ) {
            column->dropBlocksAboveEmptySpaces();
        }
    }
}