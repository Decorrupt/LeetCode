#include "pch.h"

int main()
{
    cout << "****************************Project LeetCode Start Run!*****************************" << endl << endl;

    SolutionMgr mgr(SolutionMgr::include);
    mgr.setExcludeRule();
    mgr.RunTest();

    cout << endl << "*****************************Project LeetCode Run Over!*****************************" << endl;
    return 0;
}