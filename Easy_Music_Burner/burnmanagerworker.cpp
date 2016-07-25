#include "burnmanagerworker.h"

BurnManagerWorker::BurnManagerWorker(BurnManager *BurnManagetPtr,int TaskType)
{
    this->CDRTools = BurnManagetPtr;
    this->WorkType = TaskType;
}

void BurnManagerWorker::doWork()
{

    switch(this->WorkType)
    {
    case 1:

        this->CDRTools->GetDiscWriters();

    default:
        ;

    }
    //Sleep(10000);    
    emit Finished();
     cout<<"THREAD FINISH"<<endl;
    return;
}

string BurnManagerWorker::getStdOut() const
{
    return StdOut;
}

string BurnManagerWorker::getErrOut() const
{
    return ErrOut;
}
