#include "../src/BaseFileMoved.hpp"
#include <iostream>
#include <cstring>
#include <utility> // for std::move

using namespace std;

void test_file_operations(BaseFile& file) {
    if (file.is_open()) {
        cout << "File is open for operations" << endl;
        
        //srite some data
        const char* test_data = "Hello, Move Semantics!";
        size_t bytes_written = file.write(test_data, strlen(test_data));
        cout << "Wrote " << bytes_written << " bytes to file" << endl;
        
        //read them back
        file.seek(0); 
        char buffer[100];
        size_t bytes_read = file.read(buffer, sizeof(buffer) - 1);
        buffer[bytes_read] = '\0'; // Null-terminate
        
        cout << "Read " << bytes_read << " bytes: " << buffer << endl;
    } else {
        cout << "File could not be opened for operations" << endl;
    }
}

int main() {
    cout << "\n=== Testing BaseFile Move Operations ===\n" << endl;
    
    //create some file
    const char* filename = "move_test.txt";
    
    {
        cout << "1. Creating first BaseFile object" << endl;
        BaseFile file1(filename, "w+");
        
        // Can't do this - copy operations are deleted:
        // BaseFile file1_copy = file1; // Error!
        // BaseFile file1_copy2(file1); // Error!
        
        cout << "2. Moving file1 into file2 using move constructor" << endl;
        BaseFile file2(std::move(file1));
        
        cout << "3. Checking if file1 is still usable after being moved from" << endl;
        if (file1.is_open()) {
            cout << "  ERROR: file1 is still open after move!" << endl;
        } else {
            cout << "  Good: file1 is no longer usable after move" << endl;
        }
        
        cout << "4. Performing operations on file2" << endl;
        test_file_operations(file2);
        
        cout << "5. Creating file3 and moving file2 into it using move assignment" << endl;
        BaseFile file3;
        file3 = std::move(file2);
        
        cout << "6. Checking if file2 is still usable after being moved from" << endl;
        if (file2.is_open()) {
            cout << "  ERROR: file2 is still open after move!" << endl;
        } else {
            cout << "  Good: file2 is no longer usable after move" << endl;
        }
        
        cout << "7. Performing operations on file3" << endl;
        test_file_operations(file3);
        
        // file3 will be automatically closed when it goes out of scope
    }
    
    cout << "\n8. All objects have been destroyed" << endl;
    
    return 0;
}