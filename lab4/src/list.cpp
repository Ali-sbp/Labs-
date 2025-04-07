#include "list.hpp"
#include "Circle.hpp"
#include "iostream"
#include "cstddef"
#include <fstream>

List::List() : Head(Node()), Tail(Node()), M_size(0) {
    Head.setNext(&Tail);
    Tail.setPrev(&Head);
}
List::List(Node head, Node tail, size_t m_size) : Head(head), Tail(tail), M_size(m_size) {}
//destructor
List::~List(){
    List::clear(); //smile
}
//methods
void List::addToFront(const Circle& c){
    Circle circleCopy(c); //~~> safer to create a copy of refrance
    Node* newNode = new Node(&Head,Head.getNext(),&circleCopy);
    M_size ++;
    //delete circleCopy;
    //~~>Node constructer automatically updates, no need for me to update addresses again
    //will be properly deleted with any clear() call 
}
void List::addToEnd(const Circle& c){
    Circle circleCopy(c); //~~> safer to create a copy of refrance
    Node* newNode = new Node(Tail.getPrev(),&Tail,&circleCopy);
    M_size ++;
    //same as above
}
size_t List::size()const {
    //if (Tail.getNext() == Head.getPrev()) return 0;
    return M_size;
    //return &Head - &Tail; // ???
}
bool List::isEmpty()const {
    return (M_size == 0);
}
//changed from Circle* c ~~> Circle& c for consistancy for all methods
//flag~~
bool List::removeFirst(const Circle& c){
    Node* current = Head.getNext();
    while(current != &Tail){
        if (current->getData() == c) {
            delete current; //~~> destructor reconnects
            M_size --; 
            return true;
        }
        current = current->getNext();
    }
    return false;
}
////changed from Circle* c ~~> Circle& c for consistancy for all methods
//flag~~
/*size_t List::removeAll(const Circle& c){
    size_t counter = 0;
    Node* current = Head.getNext();
    while(current != &Tail){
        if (current->m_Data == c){
            Node* nextNode= current->getNext();
            delete current; //~~>destructor reconnects
            current = nextNode;
            M_size --;
            counter++;
        }
        else{//~~> only advances if we didn't delete
        current = current->getNext();
        }
    }
    return counter;
}*/
size_t List::removeAll(const Circle& c) {
    size_t counter = 0;
    Node* current = Head.getNext();
    std::cout << "Starting removeAll with list size: " << M_size << std::endl;
    
    while(current != &Tail) {
        bool matches = (current->getData() == c);
        std::cout << "Checking node with circle: center=(" 
                  << current->getData().getCenter().getX() << "," 
                  << current->getData().getCenter().getY() << "), radius=" 
                  << current->getData().getRadius() 
                  << " - Match: " << (matches ? "YES" : "NO") << std::endl;
        
        if (matches) {
            Node* nextNode = current->getNext();
            delete current; 
            current = nextNode;
            M_size--;
            counter++;
            std::cout << "Removed a circle, counter now: " << counter << std::endl;
        }
        else {
            current = current->getNext();
        }
    }
    
    std::cout << "Finished removeAll, removed " << counter << " circles, size now: " << M_size << std::endl;
    return counter;
}
void List::clear(){ // not sure
    Node* current = Head.getNext();
    while(current != &Tail){
        Node* nextCur= current->getNext();
        delete current; //des reconnects??
        current = nextCur;
    }
    Head.setNext(&Tail);
    Tail.setPrev(&Head);
    M_size = 0;
}
/*void List::sort(){
    if (M_size == 1) return;

    for (Node* i = Head.pNext; i != &Tail ; i=i->pNext ){
        for(Node* j = i ; j != &Tail ; j = j->pNext){
            if (j->m_Data.getArea() > j->pNext->m_Data.getArea()){
                Circle temp = j->m_Data;
                j->m_Data = j->pNext->m_Data;
                j->pNext->m_Data = temp;
            }
        }
    }
    
}*/
void List::sort() {
    if (M_size <= 1) return; 

    bool swapped;
    do {
        swapped = false;
        Node* current = Head.getNext();
        
        while (current != &Tail && current->getNext() != &Tail) {
            
            if (current->getData().getArea() > current->getNext()->getData().getArea()) {
                //~~> swap the Circle objects
                Circle temp = current->getData();
                current->setData(current->getNext()->getData());
                current->getNext()->setData(temp);
                swapped = true;
            }
            current = current->getNext();
        }
    } while (swapped);
}
//optional methods
//pointer to circle at given index (if exists)
Circle* List::getCircleAt(size_t index) const {
    
    if (index >= M_size) {
        return nullptr;
    }
    Node* current = Head.getNext();
    size_t currentIndex = 0;
    
    while (current != &Tail && currentIndex < index) {
        current = current->getNext();
        currentIndex++;
    }
    if (current == &Tail) {
        return nullptr;
    }
    return new Circle(current->getData());
}
//find a Node containing a specific circle
Node* List::find(const Circle& c) const {
    Node* current = Head.getNext();
    while (current != &Tail) {
        if (current->getData() == c) {
            return current;
        }
        current = current->getNext();
    }
    return nullptr; //~~> doesn;t exist
}
//number of circles with radius greater than a 'radius'
size_t List::countCirclesWithRadiusGreaterThan(double radius) const {
    size_t count = 0;
    Node* current = Head.getNext();
    
    while (current != &Tail) {
        if (current->getData().getRadius() > radius) {
            count++;
        }
        current = current->getNext();
    }
    
    return count;
}

//I/O stream 
std::ostream& operator<<(std::ostream& os, const List& list){
    Node* current = list.Head.getNext();
    while (current != &list.Tail){
        os << "center: (" << current->getData().getCenter().getX() <<
         " ," << current->getData().getCenter().getY() << ") , Radius :" 
         << current->getData().getRadius() << " , Area :" << 
         current->getData().getArea() << "\n";
        current = current->getNext();
    }
    return os;
}
// save to file
void List::saveToFile(const std::string& filename) const{
    std::ofstream outFile(filename);
    if(!outFile.is_open()){
        std::cerr << "Error: Could not open file '" << filename <<
         "' for writing." << std::endl;
        return;
    }
    try{
    outFile << M_size << std::endl;
    if (outFile.fail()) {
        throw std::runtime_error("Failed to write list size to file");
    }
    Node* current = Head.getNext();
    size_t count = 0;
    while(current != &Tail){
                outFile << current->getData().getCenter().getX() << ' '
                << current->getData().getCenter().getY() << ' ' << 
                current->getData().getRadius() << std::endl;
        if (outFile.fail()) {
            throw std::runtime_error("Failed to write Circle data to file at position " + std::to_string(count));
        }

        current = current->getNext();
        count++;
    }
        //verification for number of elements
        if (count != M_size) {
            std::cerr << "Warning: Expected to write " << M_size << " elements, but wrote " << count << std::endl;
       }
       std::cout << "Successfully saved " << count << " elements to file '" << filename << "'" << std::endl;

    }
    catch (const std::exception& e){
        std::cerr << "Error writing to file: " << e.what() << std::endl;
    }
    outFile.close();
}
// load from file 
void List::loadFromFile(const std::string& filename){
    std::ifstream inFile(filename);
    if(!inFile.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "' for reading." << std::endl;
        return;
    }
    try {   
        clear();
        size_t numberOfElements;
        inFile >> numberOfElements;
        
        if (inFile.fail()) {
            throw std::runtime_error("Failed to read number of elements from file");
        }

        for (size_t i = 0 ; i <numberOfElements ; i++){
        double x, y , radius;

        inFile >> x >> y >> radius;
        //write fail error handle
        if (inFile.fail()) {
            throw std::runtime_error("Error reading Circle data at position " + std::to_string(i));
        }
        //error check for negative radius
        if (radius < 0) {
            std::cerr << "Warning: Found negative radius " << radius << " at position " 
                     << i << ". Setting to 0." << std::endl;
            radius = 0;
        }

        Circle newCircle(x, y, radius);
        addToEnd(newCircle);
        
        }
        //debug flag ~~> load successful
        std::cout << "Successfully loaded " << M_size << " elements from file '" << filename << "'" << std::endl;

        //check end of the file (good practice)
        std::string extraData;
        if (inFile >> extraData) {
            std::cerr << "Warning: Unexpected extra data found in file after reading expected elements." << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Error reading from file: " << e.what() << std::endl;
        clear(); // If an error occurs ~~> list is in a valid state
       
    }
    inFile.close();
}