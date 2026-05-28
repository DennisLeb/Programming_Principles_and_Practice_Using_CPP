// 19/03/2026
// Chapter12.02.cpp
// Exercises

//
// [2] Try to copy a 'Shape'. What happens?
// 
//     Answer:
//         The compiler doesn't allow it. Error E1776 is thrown, which means that the function I'm trying to use has been deleted.
//         This line in the 'Shape' class is responsible:
//             Shape(const Shape&) = delete;
// 
// [3] Define an abstract class and try to define an object of that type. What happens?
//     
//     Answer:
//         The compiler doesn't allow this either. Error E0322 is thrown, stating that 'Abstract' is an abstract class and referring to the function 'pure_virtual_func()' as the culprit.
//

#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

/*----------------------------------------*\
| Class Definitions                        |
\*----------------------------------------*/
struct Abstract
{
	Abstract() {}

	virtual int pure_virtual_func() = 0;
};

/*----------------------------------------*\
| Main                                     |
\*----------------------------------------*/
int main()
{
	try
	{
		// Copying Shapes //
		Rectangle rect{ {50, 50}, 25, 25 };
		Rectangle rect_2 = rect;

		// Defining an abstract class object //
		Abstract abst;

		return 0;
	}
	catch (exception &e)
	{
		cerr << "error: " << e.what() << endl;
		return 1;
	}
	catch (...)
	{
		cerr << "unknown error" << endl;
		return 2;
	}
}
