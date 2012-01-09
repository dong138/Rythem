#ifndef QPROXYSERVER_H
#define QPROXYSERVER_H

#include <QMutex>
#include <QMutexLocker>
#include <QTcpServer>
#include <qiconnectiondata.h>
#include <QVector>
class QiPipe;
class QiConnectionData;
#include <QSharedPointer>

class QiProxyServer : public QTcpServer{
        Q_OBJECT
    public:
        explicit QiProxyServer(QObject *parent = 0);
         ~QiProxyServer();
        
    signals:
        void newPipe(ConnectionData_ptr);
        void pipeUpdate(ConnectionData_ptr);
    public slots:
        void onPipeConnected(ConnectionData_ptr);
        void onPipeComplete(ConnectionData_ptr);
        void onPipeError(ConnectionData_ptr);
    protected:
        void incomingConnection(int handle);

        QMap<int,QThread*> threads;
        QMap<int,QiPipe*> pipes;
    private:
        QiPipe* addPipe(int socketDescriptor);
        bool removePipe(int socketId);
        void removeAllPipe();

        QMutex mutex;

        static QMutex connectionIdMutex;
        static int connectionId;
    public:
        static int nextConnectionId(){
            QMutexLocker locker(&connectionIdMutex);
            Q_UNUSED(locker)
            connectionId++;
            return connectionId;
        }
        
};

#endif // QPROXYSERVER_H