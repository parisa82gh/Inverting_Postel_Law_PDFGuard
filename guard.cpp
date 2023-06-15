//
//  guard_p3.cpp
//  
//
//  Created by Parisa Gholampour on 5/6/21.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, const char* argv[]) {
   if (argc != 2) return -1;
   // Define Variables
   string fileName(argv[1]);
    
   // Action function that we are looking for
   const string action_tags[6] = {"/URI","/Launch","/JavaScript","/GoTo","/GoToR","/GoToE"};
    
    // Compression Encryption Filters
   const string filters_tags[11] = {"/ASCIIHexDecode","/ASCII85Decode","/LZWDecode",
       "/FlateDecode","/RunLengthDecode", "/CCITTFaxDecode","/JBIG2Decode",
       "/DCTDecode","/JPXDecode","/Crypt","/Encrypt"};
    
   // Selected Font type, any font can be selected
   const string font[3] = {"Times","DejaVuSans","Serif"};
   const string desired_image = "/XObject";
    
   bool pass = true;
   bool font_pass = true;
   bool image_exist = false;
   string str = "";
   ifstream pdfFile(fileName);
    
   // Read PDF file Meta Data
   while (getline(pdfFile, str)) {
       // Save Filter tag in a variable for filter type detection
       size_t image_found = str.find(desired_image);
       // Checking available filters
       if (image_found != string::npos) {
               cout << "image exists" << endl;
               image_exist = true;
           }
       // Save FontName tag
       size_t font_found = str.find("/FontName");
       // Checking font existence
       if (font_found != string::npos){
               size_t font_0_found = str.find(font[0]);
               size_t font_1_found = str.find(font[1]);
               size_t font_2_found = str.find(font[2]);
           
               if ((font_0_found != string::npos) || (font_1_found != string::npos)
                   || (font_2_found != string::npos)){
                   cout << "font passes" << endl;
                   font_pass = true;
               }
               else {
                   cout << "font fails" << endl;
                   font_pass = false;
                   break;
           }
       }
       // Get out of the while loop of font didn't pass
       if(!font_pass)
           break;
       
       // Checking compression/encryption existence
       for (int i = 0; i< 11; i++) {
           size_t filter_found = str.find(filters_tags[i]);
           if (filter_found != string::npos) {
               cout << "PDF has compression/encryption: " << filters_tags[i] << endl;
               pass = false;
               break;
               //goto Result;
           }
       }
       // Get out of the while loop if compression/encryption exist
       if(!pass)
           break;
       
       // Checking action existence
       for (int i = 0; i< 6; i++) {
           size_t action_found = str.find(action_tags[i]);
           if (action_found != string::npos) {
               cout << "PDF has action functions: " << action_tags[i] << endl;
               pass = false;
               break;
           }
       }
       // Get out of the while loop if action function exist
       if(!pass)
           break;
   }

    if (image_exist){
        if(pass && font_pass) {
        cout << "overall :: Pass" << endl;
        }
        else
        {
            cout << "overall :: Fail" << endl;
        }
    }
    else if (pass && font_pass){
        cout << "overall :: Pass" << endl;
    }
    else{
        cout << "overall :: Fail" << endl;
    }
    
   return 0;
}


