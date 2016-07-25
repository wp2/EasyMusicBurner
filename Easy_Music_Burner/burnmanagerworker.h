#ifndef BURNMANAGERWORKER_H
#define BURNMANAGERWORKER_H

//#include <QObject>
#include "burnmanager.h"
#include "includeheaders.h"
class BurnManagerWorker : public QObject
{
    Q_OBJECT
public:

    BurnManagerWorker(BurnManager *BurnManagetPtr,int TaskType);

    string getErrOut() const;

    string getStdOut() const;

signals:

public slots:
    void doWork();
private:
    int WorkType;
    string ErrOut;
    string StdOut;
    BurnManager *CDRTools;
signals:
    void Finished();
};

#endif // BURNMANAGERWORKER_H
