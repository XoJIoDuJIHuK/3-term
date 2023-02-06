#include "FST.h"
using namespace std;

void main()
{
    /*FST fst1("aaabbbaba", 4,
        NODE(3, RELATION('a', 0), RELATION('b', 0), RELATION('a', 1)),
        NODE(1, RELATION('b', 2)),
        NODE(1, RELATION('a', 3)),
        NODE());
    if (execute(fst1))
    {
        cout << "Sequence " << fst1.std::string << " recognized\n";
    }
    else cout << "Sequence " << fst1.std::string << " not recognized\n";*/
    FSTN::FST fst1("return  calc;  ;calc; ;calc;  ;end;", 6,
        FSTN::NODE(1, FSTN::RELATION("return", 1)),
        FSTN::NODE(3, FSTN::RELATION(" ", 1), FSTN::RELATION("calc;", 3), FSTN::RELATION("print", 3)),
        FSTN::NODE(3, FSTN::RELATION(" ", 3), FSTN::RELATION("calc;", 3), FSTN::RELATION("print", 3)),
        FSTN::NODE(4, FSTN::RELATION(";", 2), FSTN::RELATION(";", 4), FSTN::RELATION(" ", 3), FSTN::RELATION("end;", 5)),
        FSTN::NODE(1, FSTN::RELATION(" ", 4), FSTN::RELATION("end;", 5)),
        FSTN::NODE());
    if (execute(fst1))
    {
        cout << "Sequence " << fst1.String << " recognized\n";
    }
    else cout << "Sequence " << fst1.String << " not recognized\n";

    FSTN::FST fst2("returncalc; ;end;", 6,
        FSTN::NODE(1, FSTN::RELATION("return", 1)),
        FSTN::NODE(3, FSTN::RELATION(" ", 1), FSTN::RELATION("calc;", 3), FSTN::RELATION("print", 3)),
        FSTN::NODE(3, FSTN::RELATION(" ", 3), FSTN::RELATION("calc;", 3), FSTN::RELATION("print", 3)),
        FSTN::NODE(4, FSTN::RELATION(";", 2), FSTN::RELATION(";", 4), FSTN::RELATION(" ", 3), FSTN::RELATION("end;", 5)),
        FSTN::NODE(1, FSTN::RELATION(" ", 4), FSTN::RELATION("end;", 5)),
        FSTN::NODE());
    if (execute(fst2))
    {
        cout << "Sequence " << fst2.String << " recognized\n";
    }
    else cout << "Sequence " << fst2.String << " not recognized\n";

    FSTN::FST fst3("return  calc; ; end;", 6,
        FSTN::NODE(1, FSTN::RELATION("return", 1)),
        FSTN::NODE(3, FSTN::RELATION(" ", 1), FSTN::RELATION("calc;", 3), FSTN::RELATION("print", 3)),
        FSTN::NODE(3, FSTN::RELATION(" ", 3), FSTN::RELATION("calc;", 3), FSTN::RELATION("print", 3)),
        FSTN::NODE(4, FSTN::RELATION(";", 2), FSTN::RELATION(";", 4), FSTN::RELATION(" ", 3), FSTN::RELATION("end;", 5)),
        FSTN::NODE(1, FSTN::RELATION(" ", 4), FSTN::RELATION("end;", 5)),
        FSTN::NODE());
    if (execute(fst3))
    {
        cout << "Sequence " << fst3.String << " recognized\n";
    }
    else cout << "Sequence " << fst3.String << " not recognized\n";

    FSTN::FST fst4("return print ; end;", 6,
        FSTN::NODE(1, FSTN::RELATION("return", 1)),
        FSTN::NODE(3, FSTN::RELATION(" ", 1), FSTN::RELATION("calc;", 3), FSTN::RELATION("print", 3)),
        FSTN::NODE(3, FSTN::RELATION(" ", 3), FSTN::RELATION("calc;", 3), FSTN::RELATION("print", 3)),
        FSTN::NODE(4, FSTN::RELATION(";", 2), FSTN::RELATION(";", 4), FSTN::RELATION(" ", 3), FSTN::RELATION("end;", 5)),
        FSTN::NODE(1, FSTN::RELATION(" ", 4), FSTN::RELATION("end;", 5)),
        FSTN::NODE());
    if (execute(fst4))
    {
        cout << "Sequence " << fst4.String << " recognized\n";
    }
    else cout << "Sequence " << fst4.String << " not recognized\n";

    FSTN::FST fst5("return calc; ;    end;", 6,
        FSTN::NODE(1, FSTN::RELATION("return", 1)),
        FSTN::NODE(3, FSTN::RELATION(" ", 1), FSTN::RELATION("calc;", 3), FSTN::RELATION("print", 3)),
        FSTN::NODE(3, FSTN::RELATION(" ", 3), FSTN::RELATION("calc;", 3), FSTN::RELATION("print", 3)),
        FSTN::NODE(4, FSTN::RELATION(";", 2), FSTN::RELATION(";", 4), FSTN::RELATION(" ", 3), FSTN::RELATION("end;", 5)),
        FSTN::NODE(1, FSTN::RELATION(" ", 4), FSTN::RELATION("end;", 5)),
        FSTN::NODE());
    if (execute(fst5))
    {
        cout << "Sequence " << fst5.String << " recognized\n";
    }
    else cout << "Sequence " << fst5.String << " not recognized\n";

    FSTN::FST fst6("return print ;end;", 6,
        FSTN::NODE(1, FSTN::RELATION("return", 1)),
        FSTN::NODE(3, FSTN::RELATION(" ", 1), FSTN::RELATION("calc;", 3), FSTN::RELATION("print", 3)),
        FSTN::NODE(3, FSTN::RELATION(" ", 3), FSTN::RELATION("calc;", 3), FSTN::RELATION("print", 3)),
        FSTN::NODE(4, FSTN::RELATION(";", 2), FSTN::RELATION(";", 4), FSTN::RELATION(" ", 3), FSTN::RELATION("end;", 5)),
        FSTN::NODE(1, FSTN::RELATION(" ", 4), FSTN::RELATION("end;", 5)),
        FSTN::NODE());
    if (execute(fst6))
    {
        cout << "Sequence " << fst6.String << " recognized\n";
    }
    else cout << "Sequence " << fst6.String << " not recognized\n";

    FSTN::FST fst7("return print ;print  ;print ;  end;", 6,
        FSTN::NODE(1, FSTN::RELATION("return", 1)),
        FSTN::NODE(3, FSTN::RELATION(" ", 1), FSTN::RELATION("calc;", 3), FSTN::RELATION("print", 3)),
        FSTN::NODE(3, FSTN::RELATION(" ", 3), FSTN::RELATION("calc;", 3), FSTN::RELATION("print", 3)),
        FSTN::NODE(4, FSTN::RELATION(";", 2), FSTN::RELATION(";", 4), FSTN::RELATION(" ", 3), FSTN::RELATION("end;", 5)),
        FSTN::NODE(1, FSTN::RELATION(" ", 4), FSTN::RELATION("end;", 5)),
        FSTN::NODE());
    if (execute(fst7))
    {
        cout << "Sequence " << fst7.String << " recognized\n";
    }
    else cout << "Sequence " << fst7.String << " not recognized\n";

    FSTN::FST fst8("return return print ;print  ;print ;  end;", 6,
        FSTN::NODE(1, FSTN::RELATION("return", 1)),
        FSTN::NODE(3, FSTN::RELATION(" ", 1), FSTN::RELATION("calc;", 3), FSTN::RELATION("print", 3)),
        FSTN::NODE(3, FSTN::RELATION(" ", 3), FSTN::RELATION("calc;", 3), FSTN::RELATION("print", 3)),
        FSTN::NODE(4, FSTN::RELATION(";", 2), FSTN::RELATION(";", 4), FSTN::RELATION(" ", 3), FSTN::RELATION("end;", 5)),
        FSTN::NODE(1, FSTN::RELATION(" ", 4), FSTN::RELATION("end;", 5)),
        FSTN::NODE());
    if (execute(fst8))
    {
        cout << "Sequence " << fst8.String << " recognized\n";
    }
    else cout << "Sequence " << fst8.String << " not recognized\n";

    FSTN::FST fst9("return print ;print  ;print ;", 6,
        FSTN::NODE(1, FSTN::RELATION("return", 1)),
        FSTN::NODE(3, FSTN::RELATION(" ", 1), FSTN::RELATION("calc;", 3), FSTN::RELATION("print", 3)),
        FSTN::NODE(3, FSTN::RELATION(" ", 3), FSTN::RELATION("calc;", 3), FSTN::RELATION("print", 3)),
        FSTN::NODE(4, FSTN::RELATION(";", 2), FSTN::RELATION(";", 4), FSTN::RELATION(" ", 3), FSTN::RELATION("end;", 5)),
        FSTN::NODE(1, FSTN::RELATION(" ", 4), FSTN::RELATION("end;", 5)),
        FSTN::NODE());
    if (execute(fst9))
    {
        cout << "Sequence " << fst9.String << " recognized\n";
    }
    else cout << "Sequence " << fst9.String << " not recognized\n";

    FSTN::FST fst10("return print ;print  ; qwe print ;end;", 6,
        FSTN::NODE(1, FSTN::RELATION("return", 1)),
        FSTN::NODE(3, FSTN::RELATION(" ", 1), FSTN::RELATION("calc;", 3), FSTN::RELATION("print", 3)),
        FSTN::NODE(3, FSTN::RELATION(" ", 3), FSTN::RELATION("calc;", 3), FSTN::RELATION("print", 3)),
        FSTN::NODE(4, FSTN::RELATION(";", 2), FSTN::RELATION(";", 4), FSTN::RELATION(" ", 3), FSTN::RELATION("end;", 5)),
        FSTN::NODE(1, FSTN::RELATION(" ", 4), FSTN::RELATION("end;", 5)),
        FSTN::NODE());
    if (execute(fst10))
    {
        cout << "Sequence " << fst10.String << " recognized\n";
    }
    else cout << "Sequence " << fst10.String << " not recognized\n";
}