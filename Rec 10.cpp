//
//  main.cpp
//  Rec 10
//

#include <iostream>
#include <vector>
using namespace std;

class PrintedMaterial {
public:
    PrintedMaterial(unsigned numPages)
    : numOfPages(numPages)
    {}
    
    virtual void displayNumPages() const = 0;
    
private:
    unsigned numOfPages;
};


void PrintedMaterial::displayNumPages() const {
    cout << numOfPages << endl;
}





class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned numPages)
    : PrintedMaterial(numPages)
    {}
    
    void displayNumPages() const {
        cout << "Magazine.\n"<<endl;
        
        PrintedMaterial::displayNumPages();
    }
    
private:
};







class Book : public PrintedMaterial {
public:
    Book(unsigned numPages)
    : PrintedMaterial(numPages)
    {}
    
private:
};

class TextBook : public Book {
public:
    TextBook(unsigned numPages, unsigned numIndxPgs)
    : Book(numPages),
    numOfIndexPages(numIndxPgs)
    {}
    
    void displayNumPages() const {
        cout <<  "Textbook.\n";
        cout << "Pages: ";
        PrintedMaterial::displayNumPages();
        cout << "Index pages: ";
        cout << numOfIndexPages << endl;
    }
    
private:
    unsigned numOfIndexPages;
};






class Novel : public Book {
public:
    Novel(unsigned numPages)
    : Book(numPages)
    {}
    void displayNumPages() const
    {
        cout << "=====================================\n" << endl;
        PrintedMaterial::displayNumPages();
        cout << "=====================================\n" << endl;
    }
    
private:
};



int main() {
    TextBook text(5430, 23);
    Novel novel(213);
    Magazine mag(6);
    
    cout << "\nEach displays its number of pages:\n" << endl;
    text.displayNumPages();
    novel.displayNumPages();
    mag.displayNumPages();
    cout << "=============\n";
    
    cout << "Vector stored" << endl;
    vector< PrintedMaterial* > allThemPrinties;
    allThemPrinties.push_back(&text);
    allThemPrinties.push_back(&novel);
    allThemPrinties.push_back(&mag);
    for(size_t ndx=0; ndx < allThemPrinties.size(); ++ ndx) {
        allThemPrinties[ndx]->displayNumPages();
        cout << endl;
    }
    cout << "=============\n";
    for (const PrintedMaterial* pmPtr : allThemPrinties) {
        pmPtr->displayNumPages();
        cout << endl;
    }
}
