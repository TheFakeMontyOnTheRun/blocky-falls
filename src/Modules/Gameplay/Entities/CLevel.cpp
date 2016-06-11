#include <iostream>
#include <algorithm>
#include <random>
#include <set>

#include "Vipper/Vipper.h"
#include "Modules/Gameplay/Entities/CColumn.h"
#include "Modules/Gameplay/Entities/CLevel.h"

namespace BlockyFalls {
  
    void CLevel::addRandomColumn() {
        
        auto column = std::make_shared<CColumn>();
        mColumns.insert( mColumns.begin(), column );

        // if ( mColumns.size() % 2 == 0 ) {
        //     for ( int c = 0; c < CColumn::kColumnHeight; ++c ) {
        //         mColumns[ 1 ]->mBlocks[ c ] = CColumn::EColour::eRed;
        //     }
        // }
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

    bool CLevel::isColumnEmpty( int index ) {
        return mColumns[ index ]->isEmpty();
    }
    
    bool CLevel::canBreakAt( int x, int y ) {
        return colourAt( x, y )  != CColumn::EColour::eNothing && ( 
            colourAt( x, y ) == colourAt( x + 1, y) ||
            colourAt( x, y ) == colourAt( x - 1, y) ||
            colourAt( x, y ) == colourAt( x, y + 1) ||
            colourAt( x, y ) == colourAt( x, y - 1)
        );
    }
    
    std::vector<std::pair<int, int>> CLevel::propagate( int x, int y ) {
        
        std::vector<std::pair<int, int>> toReturn;
                
        if ( x >= mColumns.size() || x < 0 ) {
            return toReturn;
        }
        
        if ( y >= CColumn::kColumnHeight || y < 0 ) {
            return toReturn;
        }
        
        auto originalColour = colourAt( x, y ); 
        
        if ( originalColour == CColumn::EColour::eNothing ) {
            return toReturn;
        }
        
        toReturn.push_back( std::pair<int, int>(x, CColumn::kColumnHeight - y - 1) );
        mColumns[ x ]->breakBlockAt( y );
        
        if ( originalColour == colourAt( x + 1, y) ) {
            auto toAdd = propagate( x + 1, y );
            toReturn.insert( toReturn.end(), toAdd.begin(),toAdd.end() );        
        }
            
        if ( originalColour == colourAt( x - 1, y) ) {
            auto toAdd = propagate( x - 1, y );
            toReturn.insert( toReturn.end(), toAdd.begin(),toAdd.end() );
        }
            
        if ( originalColour == colourAt( x, y + 1) ) {
            auto toAdd = propagate( x, y + 1);
            toReturn.insert( toReturn.end(), toAdd.begin(),toAdd.end() );
        }
            
        if ( originalColour == colourAt( x, y - 1)  ) {
            auto toAdd = propagate( x, y - 1);
            toReturn.insert( toReturn.end(), toAdd.begin(),toAdd.end() );
        }
        
        return toReturn;
    }
    
    
    std::vector<std::pair<int, int>> CLevel::breakBlockAt( std::pair<int, int> position ) {        
        int x = position.first;
        int y = position.second;
        auto colour = colourAt( x, y );
        std::vector<std::pair<int, int>> toReturn;
        
        if ( canBreakAt( x, y ) ) {
            auto toAdd = propagate( x, y ); 
            toReturn.insert( toReturn.end(), toAdd.begin(),toAdd.end() );
        }
        
        return toReturn;
    }
    
    void CLevel::collapseEmptyColumns() {     
        static const auto predicate = [](std::shared_ptr<CColumn> c) {
            return c->isEmpty();
        };
        
        mColumns.erase( std::remove_if( mColumns.begin(), mColumns.end(), predicate), mColumns.end() );
    }

    std::set< std::pair<int, int >> CLevel::getColumnCollapseList() {
        std::set< std::pair<int, int >> toReturn;
        
        static const auto predicate = [](std::shared_ptr<CColumn> c) {
            return c->isEmpty();
        };

        size_t size = mColumns.size();
        int emptyColumns = 0;
        int position = 0;

        for ( auto& column : mColumns ) {

            if ( column->isEmpty() ) {
                emptyColumns++;
            } else {

                if ( emptyColumns > 0 ) {
                    int from = position;
                    int to = position - emptyColumns;
                    auto path = std::pair<int, int>( from, to);
                    // std::cout << "column " << from << " to position " << to << std::endl;
                    toReturn.insert(  path );
                }
            }
            ++position;
        }
        return toReturn;
    }
    
    std::vector<std::tuple<std::pair<int,int>, std::pair<int, int>, CColumn::EColour>> CLevel::getDropList() {
        std::vector<std::tuple<std::pair<int,int>, std::pair<int, int>, CColumn::EColour>> paths;

        int x = 0;
        for ( auto& column : mColumns ) {
            auto toAdd = column->getDropList( x++ );
            paths.insert( paths.end(), toAdd.begin(), toAdd.end() );
        }

        return paths;
    }

    void CLevel::dropBlocksAboveEmptySpaces( int column ) {
        mColumns[ column ] ->dropBlocksAboveEmptySpaces();
    }
    
}