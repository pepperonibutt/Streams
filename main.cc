#include <iostream>
#include <string>
#include <cassert>

#include "Serial.h"

using namespace std;

    int main() {
        cout << "Test begins\n";
        Serial s;

        assert(s.str() == "" && s.size()==0 && s.empty());

        s.put(4);
        assert(s.str() == "i\x04" && s.size()==2 && !s.empty());
        s.put('5');
        assert(s.str() == "i\x04" "c5" && s.size()==4);
        s.put(66L);
        assert(s.str() == "i\x04" "c5" "l\x10\x42" && s.size()==7);

        int i; char c; long l;

        cout << s.str() << " " << s.size() << " " << s.empty() << endl;

        s.get(i);
        cout << s.str() << " " << s.size() << " " << s.empty() << " "<< i << endl;
        assert(i == 4 && s.str() == "c5" "l\x10\x42" && s.size()==5); 
        
        try {
            s.get(c);
        } catch(string &s) {
            cout << s << endl;
        }
        //s.get(c);
        cout << s.str() << " " << s.size() << " " << s.empty() << endl;
        assert(c == '5' && s.str() == "l\x10\x42" && s.size()==3); 

        // The next item is a long.  Try to get a char, which will fail.
        bool caught = false;
        try {
            s.get(c);
       }
       catch (string st) {
             caught = true;
       }
       assert(caught);
       
       cout << "test long: " << s.str() << " " << s.size() << " " << s.empty() << endl;
        s.get(l);
        cout << "test long: " << s.str() << " " << s.size() << " " << s.empty() << endl;

        assert(l == 66 && s.empty());

        //s.str("S" "\x05" "test.");
       //cout << "Final test" << s.str() << " " << s.size() << " " << s.empty() << endl;        
        //string st = "foobar";
        //s.get(st);

        //cout << "st is: " << st <<  " and s empty is " << s.empty() << endl;
        //assert(st == "xyz" && s.empty());
        cout << "Test ends\n";

        cout << "Test2 begins\n";
        Serial s1; bool b1=false; 
        //int i1; 
        long l1;

        s1+=true;
        cout << s1 << endl;
        cout << "good 1 " << endl;
        s1.put(-1);          // s = -1
        cout << s1 << endl;
        cout << "good 2 " << endl;
        const Serial t(s1);      // s = t = true -1
        assert(t == s1);
        cout << "good 3 " << endl;       
        s1.get(b1); 
        cout << "good 4 " << endl;
        assert(b1);        // s = -1
        cout << "good 5 " << endl;
        s1 = s1 + 'x';            // s = -1 'x'
        assert(s1 != t);
        s1 = (1L<<63) + t;       // s = LONG_MIN true -1
        //assert((s1+t).str() == "l\x8f\x80\0\0\0\0\0\0\0ti\x0fti\17"s);

        bool caught1 = false;
        try {
            s1.get(b1);
        }
        catch (string st) {
            caught1 = true;
        }
        assert(caught1);

        l1 <<= s1; assert(l1 == 1L<<63);   // true -1

        //const string now = "2018-04-20T13:50:13.463206";
        //s1 += now;           // true -1 now
        //s1.get(b1);           // -1 now
        //s1.get(i1);           // now
        //string foo1="bar";
        //s1.get(foo1);
        //assert(foo1 == now);

        cout << "Test2 ends\n";
        cout << "Test3 begins.\n";
        {
            OFSerial out("data");
            out << true;
            out << 'x' << 42;
        }

        IFSerial in("data");
        bool b3; char c3; int i3;
        in >> b3 >> c3;
        in >> i3;
        assert(b3);
        assert(c3 == 'x');
        assert(i3 == 42);
        assert(in);
        assert(!in.fail());
        assert(!in.eof());
        in >> i3;
        assert(!in);        // same as in.fail()
        assert(in.fail());  // a conversion (in >> i) failed
        assert(in.eof());   // we hit end-of-file


        // Read the raw datafile
        ifstream raw("data");
        string data;
        while (raw.get(c))
            data += c;
        assert(data == "t" "cx" "i\x10\x2a");   // true, 'x', 42

        // Try writing to a file that can’t be created.
        OFSerial o("/this/does/not/exist");
        assert(!o);
        assert(o.fail());
        o << 3346790;       // Must not complain, throw, or exit.
        assert(!o);
        assert(o.fail());

        cout << "Test ends.\n";

        return 0;
    }
