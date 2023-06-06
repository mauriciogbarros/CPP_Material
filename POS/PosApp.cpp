/***********************************************************************
// OOP244 Project Milestone 5: PosApp  source file
// File:    PosApp.cpp
//
// Name:    Mauricio Gomes de Barros
// Email:   mgomes-de-barros@myseneca.ca
// ID:      122509227
// Section: NCC
// Date:    04/16/2023
//
// I have done all the coding by myself and only copied the code that
// my professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////
***********************************************************************/

#include "PosApp.h"

namespace sdds
{
    // Private
    void PosApp::sortItems()
    {
        Item* tempPtr = nullptr;
        int minIndex = 0;

        if (nptr > 0)
        {
            for (int i = 0; i < nptr; i++)
            {
                minIndex = i;
                for (int j = i + 1; j < nptr; j++)
                    if (*Iptr[j] > *Iptr[minIndex])
                        minIndex = j;

                if (minIndex != i)
                {
                    tempPtr = Iptr[i];
                    Iptr[i] = Iptr[minIndex];
                    Iptr[minIndex] = tempPtr;
                }
            }
        }
    }

    std::ostream& PosApp::actionTitle(std::ostream& oStream, const char* action)
    {
        oStream << ">>>> ";
        oStream.width(72);
        oStream.fill('.');
        oStream.setf(std::ios::left);
        oStream << action << std::endl;
        oStream.unsetf(std::ios::left);
        oStream.fill(' ');

        return oStream;
    }

    int PosApp::selectItem(std::ostream& oStream, std::istream& iStream)
    {
        int rowNumber = 0;
        char enterToStart = '\0';
        bool correctInput = false;
        actionTitle(oStream, "Item Selection by row number");
        oStream << "Press <ENTER> to start....";
        while (enterToStart != '\n')
            iStream.get(enterToStart);
        iStream.clear();
        iStream.ignore(10000, '\n');
        listItems(oStream, false);
        oStream << "Enter the row number: ";
        while (!correctInput)
        {
            iStream >> rowNumber;
            if (!iStream.fail())
            {
                if (rowNumber > 0 && rowNumber <= nptr)
                    correctInput = true;
                else
                    oStream << "[1<=value<=" << nptr << "], retry: Enter the row number: ";
            }
            else
            {
                iStream.clear();
                iStream.ignore(10000, '\n');
                oStream << "Invalid Integer, try again: ";
            }
        }
        return rowNumber;
    }

    Item* PosApp::search(const char* sku)
    {
        int i = 0;
        Item* itemPtr = nullptr;
        while(i < nptr && !(*Iptr[i] == sku))
            i++;
        if(i < nptr)
            itemPtr = Iptr[i];
        return itemPtr;
    }
    //ms1
    PosApp::PosApp()
    {
        strcpy(this->fileName, "");
        this->menuSelection = -1;
    }

    PosApp::PosApp(const char* fileName)
    {
        if(fileName != nullptr)
            strcpy(this->fileName, fileName);
    }

    std::ostream& PosApp::menu(std::ostream& oStream, std::istream& iStream)
    {
        int input = -1;

        oStream << "The Sene-Store" << std::endl;
        oStream << "1- List items" << std::endl;
        oStream << "2- Add item" << std::endl;
        oStream << "3- Remove item" << std::endl;
        oStream << "4- Stock item" << std::endl;
        oStream << "5- POS" << std::endl;
        oStream << "0- exit program" << std:: endl;
        oStream << "> ";

        while (input < 0 || input > 5)
        {
            if (iStream >> input)
            {
                if (input >= 0 && input <= 5)
                    this->menuSelection = input;
                else 
                    oStream << "[0<=value<=5], retry: > ";
            }
            else
            {
                iStream.clear();
                iStream.ignore(10000, '\n');
                oStream << "Invalid Integer, try again: ";
                input = -1;
            }
        }

        return oStream;
    }

    void PosApp::run()
    {
        loadRecs(std::cout);
        while(this->menuSelection != 0)
        {
            this->menu(std::cout, std::cin);

            switch(this->menuSelection)
            {
            case 0:
                saveRecs(std::cout, this->fileName);
                break;

            case 1:
                listItems(std::cout, true);
                break;
                    
            case 2:
                addItem(std::cout, std::cin);
                break;

            case 3:
                removeItem(std::cout, std::cin);
                break;

            case 4:
                stockItem(std::cout, std::cin);
                break;

            case 5:
                POS(std::cout, std::cin);
                break;
            }
        }

        std::cout << "Goodbye!" << std::endl;
    }

    //ms5.1
    void PosApp::loadRecs(std::ostream& oStream)
    {
        char itemType = '\0';

        actionTitle(oStream, "Loading Items");

        std::ifstream input(this->fileName);

        if (input)
        {
            for (int i = 0; i < MAX_NO_ITEMS; i++)
                this->Iptr[i] = nullptr;
            this->nptr = 0;

            while (input && this->nptr <= MAX_NO_ITEMS)
            {
                itemType = input.get();
                input.ignore();
                switch (itemType)
                {
                    case 'P':
                    {
                        Iptr[nptr] = new Perishable();
                        Iptr[nptr]->load(input);
                    }
                    break;

                    case 'N':
                    {
                        Iptr[nptr] = new NonPerishable();
                        Iptr[nptr]->load(input);
                    }
                    break;
                }
                input.ignore();
                nptr++;
            }
            nptr--;
            input.close();
        }
        else
        {
            std::ofstream output(this->fileName);
            output.close();
        }
    }

    void PosApp::saveRecs(std::ostream& oStream, char* fileName)
    {
        actionTitle(oStream, "Saving Data");

        std::ofstream output(fileName);
        for (int i = 0; i < nptr; i++)
        {
            Iptr[i]->save(output);
            output.put('\n');
        }

        for (int i = 0; i < nptr; i++)
        {
            delete Iptr[i];
            Iptr[i] = nullptr;
        }
        nptr = 0;
    }

    void PosApp::listItems(std::ostream& oStream, bool displayTotalAsset)
    {
        double totalAsset = 0;

        actionTitle(oStream, "Listing Items");

        sortItems();

        oStream << " Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |" << std::endl;
        oStream << "-----|--------|--------------------|-------|---|----|---------|-------------|" << std::endl;
        for (int i = 0; i < nptr; i++)
        {
            oStream.width(4);
            oStream << i +1 << " | ";
            Iptr[i]->write(oStream);
            oStream << std::endl;
            totalAsset += Iptr[i]->cost() * Iptr[i]->quantity();
        }
        oStream << "-----^--------^--------------------^-------^---^----^---------^-------------^" << std::endl;
        if (displayTotalAsset)
        {
            oStream << "                               Total Asset: $  |       ";
            oStream.setf(std::ios::fixed);
            oStream.precision(2);
            oStream << totalAsset << "|" << std::endl;
            oStream << "-----------------------------------------------^--------------^" << std::endl << std::endl;
        }
    }

    // ms5.2
    void PosApp::addItem(std::ostream& oStream, std::istream& iStream)
    {
        char isPerishable = '\0';

        actionTitle(oStream, "Adding Item to the store");

        if (nptr < MAX_NO_ITEMS)
        {
            Item* tempPtr = nullptr;
            bool itemInGoodState = false;
            oStream << "Is the Item perishable? (Y)es/(N)o: ";
            iStream >> isPerishable;
            if (isPerishable == 'Y' || isPerishable == 'y')
                tempPtr = new Perishable();
            else if (isPerishable == 'N' || isPerishable == 'n')
                tempPtr = new NonPerishable();
            while (!itemInGoodState)
            {
                tempPtr->read(iStream);
                if (*tempPtr)
                {
                    itemInGoodState = true;
                    Iptr[nptr] = tempPtr;
                    nptr++;
                    actionTitle(oStream, "DONE!");
                }
                else
                {
                    iStream.clear();
                    iStream.ignore(10000, '\n');
                    oStream << *tempPtr << ", try again...\n";
                }
            }
        }
        else
            oStream << "Inventory Full!";
    }

    // ms5.3
    void PosApp::removeItem(std::ostream& oStream, std::istream& iStream)
    {
        int deleteIndex = 0;
        actionTitle(oStream, "Remove Item");
        deleteIndex = selectItem(oStream, iStream) - 1;
        oStream << "Removing...." << std::endl;
        Iptr[deleteIndex]->displayType(2);
        Iptr[deleteIndex]->write(oStream);
        delete Iptr[deleteIndex];
        Iptr[deleteIndex] = nullptr;
        for (int i = deleteIndex; i < nptr - 1; i++)
            Iptr[i] = Iptr[i + 1];
        Iptr[nptr - 1] = nullptr;
        nptr--;
        actionTitle(oStream, "DONE!");
    }

    // ms5.4
    void PosApp::stockItem(std::ostream& oStream, std::istream& iStream)
    {
        int selectIndex = 0;
        int quantity = 0;
        bool correctInput = false;
        actionTitle(oStream, "Select an item to stock");
        selectIndex = selectItem(oStream, iStream) - 1;
        oStream << "Selected Item:\n";
        Iptr[selectIndex]->displayType(2);
        Iptr[selectIndex]->write(oStream);
        oStream << "Enter quantity to add: ";
        while(!correctInput)
        {
            iStream >> quantity;
            if(!iStream.fail())
            {
                if(quantity >= 1 && quantity <= MAX_STOCK_NUMBER - Iptr[selectIndex]->quantity())
                {
                    *Iptr[selectIndex] += quantity;
                    actionTitle(oStream, "DONE!");
                    correctInput = true;
                }
                else
                    oStream << "[1<=value<=" << MAX_STOCK_NUMBER - Iptr[selectIndex]->quantity() << "], retry: Enter quantity to add: ";
            }
            else
            {
                oStream << "Invalid Integer, try again: ";
                iStream.clear();
                iStream.ignore(10000, '\n');
            }
        }
    }

    // ms5.5
    void PosApp::POS(std::ostream& oStream, std::istream& iStream)
    {
        Item* itemPtr = nullptr;
        Bill bill;
        char sku[MAX_SKU_LEN] = {'\0'};
        actionTitle(oStream, "Starting Point of Sale");
        iStream.ignore();
        do
        {
            oStream << "Enter SKU or <ENTER> only to end sale..." << std::endl;
            oStream << "> ";
            iStream.getline(sku, MAX_SKU_LEN, '\n');
            if (iStream && sku[0] != '\0')
            {
                itemPtr = search(sku);
                if (itemPtr)
                {
                    *itemPtr -= 1;
                    itemPtr->displayType(2);
                    itemPtr->write(oStream);
                    oStream << std::endl;
                    if (*itemPtr)
                    {
                        bill.add(itemPtr);
                        oStream << ">>>>> Added to bill" << std::endl;
                        oStream << ">>>>> Total: " << bill.total() << std::endl;
                    }
                    else
                        itemPtr->clear();
                }
                else
                    oStream << "!!!!! Item Not Found !!!!!" << std::endl;
            }
            else if (!iStream)
            {
                iStream.clear();
                iStream.ignore(10000, '\n');
                oStream << "SKU too long" << std::endl;
            }
        } while(sku[0] != '\0');
        bill.print(oStream);
        oStream.unsetf(std::ios::right);
    }

    // Helper methods
    std::ostream& operator << (std::ostream& oStream, PosApp pos)
    {
        return std::cout;
    }

    std::istream& operator >> (std::istream& iStream, PosApp pos)
    {
        return std::cin;
    }
}