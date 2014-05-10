/*
 * (C) 2014 Search for a Star
 * 
 */

#include "TargetNumberGenerator.h"
#include "GameScene.h"
#include "GridItem.h"
#include "Grid.h"

using namespace SFAS2014;

//
//
// TargetNumberGenerator class
//
//
unsigned int TargetNumberGenerator::sMinFactorsPerTarget = 3;
unsigned int TargetNumberGenerator::sMaxFactorsPerTarget = 3;

TargetNumberGenerator::TargetNumberGenerator( Grid* grid ) 
{
    // Create unallocated arrays.
    m_GridItems = new GridItem* [3*sMaxFactorsPerTarget];
    m_ValueCounts = new unsigned int [GridItem::TotalValues];

    InitialiseValueCounts( grid );

    // Generate the initial GridItems.
    for( unsigned int i = 0; i < 3 * sMaxFactorsPerTarget; i++ )
    {
        m_GridItems[i] = new GridItem( 
                0, 0, (GridItem::Shape) (IwRand() % GridItem::NumberOfShapes) );
    }
    
    // Generate the initial target numbers.
    m_TargetNumbers[0] = 0;
    m_TargetNumbers[1] = 0;
    m_TargetNumbers[2] = 0;
    GenerateTargetNumber();
    GenerateTargetNumber();
    GenerateTargetNumber();
}

TargetNumberGenerator::~TargetNumberGenerator()
{
    // Delete all the GridItems.
    for( unsigned int i = 0; i < 3 * sMaxFactorsPerTarget; i++ )
    {
        delete m_GridItems[i];
    }
    delete[] m_GridItems;
    delete[] m_ValueCounts;
}

void TargetNumberGenerator::ConsumeTargetAndGridItems()
{
    int totalGridItems = 3 * sMaxFactorsPerTarget;
    // Shift the GridItems.
    for( int i = m_GridItemCounts[0]; i < totalGridItems; i++ )
    {
        m_GridItems[i - m_GridItemCounts[0]] = m_GridItems[i];
    }
    // Generate new GridItems.
    for( int i = totalGridItems - m_GridItemCounts[0] - 1; 
            i < totalGridItems; i++ )
    {
        m_GridItems[i] = new GridItem( 0, 0, 
                (GridItem::Shape) ( IwRand() % GridItem::NumberOfShapes ) );
        
    }

    // Shift the target numbers.
    m_TargetNumbers[0] = m_TargetNumbers[1];
    m_GridItemCounts[0] = m_GridItemCounts[1];
    m_TargetNumbers[1] = m_TargetNumbers[2];
    m_GridItemCounts[1] = m_GridItemCounts[2];
    m_TargetNumbers[2] = 0;
    m_GridItemCounts[2] = 0;
    // Generate a new target number.
    GenerateTargetNumber();
}

void TargetNumberGenerator::Reset( Grid* grid )
{
    // Replace the GridItems.
    for( unsigned int i = 0; i < 3 * sMaxFactorsPerTarget; i++ )
    {
        delete m_GridItems[i];
        m_GridItems[i] = new GridItem( 
                0, 0, (GridItem::Shape) (IwRand() % GridItem::NumberOfShapes) );
    }
    // Reset the target numbers.
    m_TargetNumbers[0] = 0;
    m_TargetNumbers[1] = 0;
    m_TargetNumbers[2] = 0;
    InitialiseValueCounts( grid );
    // Generate new target numbers.
    GenerateTargetNumber();
    GenerateTargetNumber();
    GenerateTargetNumber();
}

unsigned int TargetNumberGenerator::GetFirstTarget()
{
    return m_TargetNumbers[0];
}

unsigned int TargetNumberGenerator::GetSecondTarget()
{
    return m_TargetNumbers[1];
}

unsigned int TargetNumberGenerator::GetThirdTarget()
{
    return m_TargetNumbers[2];
}

GridItem** TargetNumberGenerator::GetNextGridItems()
{
    GridItem** items = new GridItem* [ m_GridItemCounts[0] ];
    for( unsigned int i = 0; i < m_GridItemCounts[0]; i++ )
    {
        items[i] = m_GridItems[i];
    }
    return items;
}

void TargetNumberGenerator::GenerateTargetNumber()
{
    unsigned int targetNumber = 1;
    unsigned int numberOfFactors = 
            ( IwRand() % (sMaxFactorsPerTarget + 1 - sMinFactorsPerTarget) ) + 
                sMinFactorsPerTarget;

    // List the possible factors.
    unsigned int* possibleFactors = new unsigned int[GridItem::TotalValues];
    int totalPossibleFactors = 0;
    for( unsigned int i = 0; i < GridItem::TotalValues; i++ )
    {
        if( m_ValueCounts[i] > 0 )
        {
            possibleFactors[totalPossibleFactors] = GridItem::Values[i];
            totalPossibleFactors++;
        }
    }

    targetNumber = SelectFactors( 
            numberOfFactors, possibleFactors, totalPossibleFactors );

    delete[] possibleFactors;

    for( int i = 0; i < 3; i++ )
    {
        if( m_TargetNumbers[i] == 0 )
        {
            m_TargetNumbers[i] = targetNumber;
            m_GridItemCounts[i] = numberOfFactors;
            // The GridItems used to meet this target number will be replaced 
            // by new ones, so make the new values available for the next target
            // number.
            for( unsigned int j = 0; j < numberOfFactors; j++ )
            {
                AddValue( m_GridItems[j] );
            }
            break;
        }
    }
}

unsigned int TargetNumberGenerator::SelectFactors( 
        unsigned int numberOfFactors, 
        unsigned int* possibleFactors, 
        unsigned int totalPossibleFactors )
{
    unsigned int targetNumber = 1;
    for( unsigned int factor = 0; factor < numberOfFactors; factor++ )
    {
        unsigned int nextFactorIndex = IwRand() % totalPossibleFactors;
        unsigned int nextFactor = possibleFactors[nextFactorIndex];
        targetNumber *= nextFactor;
        // Decrement the available instances of the chosen factor.
        for( unsigned int i = nextFactorIndex; i < GridItem::TotalValues; i++ )
        {
            if( GridItem::Values[i] == nextFactor )
            {
                m_ValueCounts[i]--;
                // If that was the last instance of that factor, remove it as 
                // a possible factor.
                if( 0 == m_ValueCounts[i] )
                {
                    for( unsigned int j = nextFactorIndex + 1; 
                            j < totalPossibleFactors; j++ )
                    {
                        possibleFactors[j-1] = possibleFactors[j];
                    }
                }
                break;
            }
        }
    }
    return targetNumber;
}

void TargetNumberGenerator::AddValue( GridItem* item )
{
    for( unsigned int val = 0; val < GridItem::TotalValues; val++ )
    {
        if( item->GetValue() == GridItem::Values[val] )
        {
            m_ValueCounts[val] += 1;
            break;
        }
    }
}

void TargetNumberGenerator::InitialiseValueCounts( Grid* grid )
{
    for( unsigned int i = 0; i < GridItem::TotalValues; i++ )
    {
        m_ValueCounts[i] = 0;
    }
    for( unsigned int row = 0; row < grid->GetHeight(); row++ )
    {
        for( unsigned int col = 0; col < grid->GetWidth(); col++ )
        {
            GridItem* item = grid->GetItem( row, col );
            AddValue( item );
        }
    }
}
