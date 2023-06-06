/***********************************************************************
// OOP244 Project Milestone 5: PosApp header file
// File:    PosApp.h
//
// Name:    Mauricio Gomes de Barros
// Email:   mgomes-de-barros@myseneca.ca
// ID:      122509227
// Section: NCC
// Date:    04/06/2023
//
// I have done all the coding by myself and only copied the code that
// my professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////
***********************************************************************/

#ifndef SDDS_POSAPP_H_
#define SDDS_POSAPP_H_
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <fstream>
#include "Item.h"
#include "Perishable.h"
#include "NonPerishable.h"
#include "POS.h"
#include "Bill.h"

namespace sdds
{
    class PosApp
    {
    private:
        // ms1
        int menuSelection = -1;

        // ms5
        char fileName[MAX_FILENAME] = {'\0'};
        Item* Iptr[MAX_NO_ITEMS] = {{0}};
        int nptr = 0;

        void sortItems();
        std::ostream& actionTitle(std::ostream& oStream, const char* action);
        int selectItem(std::ostream& oStream, std::istream& iStream);
        Item* search(const char* sku);

    public:
        // ms1
        PosApp();
        PosApp(const char* fileName);
        PosApp(const PosApp& posApp) = delete;
        PosApp& operator = (const PosApp& posApp) = delete;
        std::ostream& menu(std::ostream& oStream, std::istream& iStream);
        void run();
        
        // ms5.1
        void loadRecs(std::ostream& oStream);
        void saveRecs(std::ostream& oStream, char* fileName);
        void listItems(std::ostream& oStream, bool displayTotalAsset);
        // ms5.2
        void addItem(std::ostream& oStream, std::istream& iStream);
        // ms5.3
        void removeItem(std::ostream& oStream, std::istream& iStream);
        // ms5.4
        void stockItem(std::ostream& oStream, std::istream& iStream);
        // ms5.5
        void POS(std::ostream& oStream, std::istream& iStream);
    };

    std::ostream& operator << (std::ostream& oStream, PosApp pos);
    std::istream& operator >> (std::istream& iStream, PosApp pos);
}

#endif // SDDS_POSAPP_H_