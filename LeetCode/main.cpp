#include "pch.h"
#include "solution.h"

int main()
{
    cout << "****************************Project LeetCode Start Run!*****************************" << endl << endl;

    SolutionMgr mgr(SolutionMgr::exclude);
    mgr.setIncludeRule(2,"2164_2");
    mgr.RunTest();

    cout << endl << "*****************************Project LeetCode Run Over!*****************************" << endl;
    return 0;
}