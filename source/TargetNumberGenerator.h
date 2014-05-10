/*
 * (C) 2014 Search for a Star
 * 
 */

#if !defined(__TARGETNUMBERGENERATOR_H__)
#define __TARGETNUMBERGENERATOR_H__


namespace SFAS2014
{
class Grid;
class GridItem;

/**
 * @class TargetNumberGenerator
 *
 * @brief Class which contains and generates the game's target numbers and 
 *        new GridItems to replace those the player clears.
 *
 */
class TargetNumberGenerator
{

public:	
    
    static unsigned int sMinFactorsPerTarget;
    static unsigned int sMaxFactorsPerTarget;

    TargetNumberGenerator( Grid* grid );
    ~TargetNumberGenerator();

    /**
     * @fn    void TargetNumberGenerator::ConsumeTargetAndGridItems();
     *
     * @brief Clears the next target number, shifts the others along by one,
     *        and generates a new one. Also clears and shifts GridItems.
     *
     */
    void ConsumeTargetAndGridItems();

    /**
     * @fn    void TargetNumberGenerator::Reset( Grid* grid );
     *
     * @brief Generates new target numbers from the given grid, and new 
     * GridItems.
     *
     */
	void Reset( Grid* grid );

    /**
     * @fn    unsigned int TargetNumberGenerator::GetFirstTarget();
     *
     * @brief Returns the first target number.
     *
     */
	unsigned int GetFirstTarget();

    /**
     * @fn    unsigned int TargetNumberGenerator::GetSecondTarget();
     *
     * @brief Returns the second target number.
     *
     */
	unsigned int GetSecondTarget();

    /**
     * @fn    unsigned int TargetNumberGenerator::GetThirdTarget();
     *
     * @brief Returns the third target number.
     *
     */
	unsigned int GetThirdTarget();

    /**
     * @fn    GridItem** TargetNumberGenerator::GetNextGridItems();
     *
     * @brief Returns an array of the next GridItems to add to the Grid when
     *        the player clears some. 
     *
     */
	GridItem** GetNextGridItems();

private: 

    unsigned int m_TargetNumbers[3];
    GridItem** m_GridItems; // Array
    // Contains the number of GridItems that make up each target number.
	unsigned int m_GridItemCounts[3];
    // Contains the number of each GridItem that is currently available for 
    // generating targets.
    unsigned int* m_ValueCounts; // Array
    
    // Generates a target number into the lowest zero-valued array slot.
    void GenerateTargetNumber();
    
    // Selects factors from the given possible factors.
    unsigned int SelectFactors( unsigned int numberOfFactors, 
                                unsigned int* possibleFactors, 
                                unsigned int totalPossibleFactors);

    // Adds a GridItem's value to those available for generating target numbers.
    void AddValue( GridItem* item );

    // Set the initial value counts from the grid.
    void InitialiseValueCounts( Grid* grid );
};
}

#endif  // __GRIDITEM_H__


