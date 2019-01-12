cmake_minimum_required(VERSION 3.12)
project(P2P)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(P2P main.cpp Network/NetworkManager.cpp Network/NetworkManager.h
        Network/RemoteNode.cpp Network/RemoteNode.h Network/Stoppable.cpp Network/Stoppable.h
        Network/Receiver.cpp Network/Receiver.h Network/Sender.cpp Network/Sender.h
        Tasks/SenderTasks/SendFilesListRequest.cpp Tasks/SenderTasks/SendFilesListRequest.h
        Tasks/SenderTasks/SenderTask.cpp Tasks/SenderTasks/SenderTask.h
        Communication/Client.cpp Communication/Client.h
        OperationCode.cpp OperationCode.h
        Tasks/SenderTasks/SendFilesList.cpp Tasks/SenderTasks/SendFilesList.h
        Communication/Server.cpp Communication/Server.h
        Tasks/ReceiverTasks/ReceiverTask.cpp Tasks/ReceiverTasks/ReceiverTask.h
        Tasks/ReceiverTasks/ReceiveFileList.cpp Tasks/ReceiverTasks/ReceiveFileList.h
        Tasks/SenderTasks/SendNodesListRequest.cpp Tasks/SenderTasks/SendNodesListRequest.h
        Tasks/SenderTasks/SendNodesList.cpp Tasks/SenderTasks/SendNodesList.h
        Controller.cpp Controller.h Network/Listener.cpp Network/Listener.h
        Tasks/ReceiverTasks/ReceiveNodesList.cpp Tasks/ReceiverTasks/ReceiveNodesList.h
        ConsoleMenu.cpp ConsoleMenu.h
        Tasks/SenderTasks/SendFile.cpp Tasks/SenderTasks/SendFile.h
        Tasks/SenderTasks/FileRequest.cpp Tasks/SenderTasks/FileRequest.h
        Tasks/ReceiverTasks/ReceiveFile.cpp Tasks/ReceiverTasks/ReceiveFile.h FileManager.cpp FileManager.h Network/FileDownloadManager.cpp Network/FileDownloadManager.h Serializers/Serializers/Output.cpp Serializers/Serializers/Output.h Serializers/Serializers/Serializer.cpp Serializers/Serializers/Serializer.h Communication/Pushers/Pusher.cpp Communication/Pushers/Pusher.h Communication/Pushers/SocketPusher.cpp Communication/Pushers/SocketPusher.h Communication/Pullers/Puller.cpp Communication/Pullers/Puller.h Communication/Pullers/SocketPuller.cpp Communication/Pullers/SocketPuller.h Serializers/Deserializers/Input.cpp Serializers/Deserializers/Input.h Serializers/Deserializers/Deserializer.cpp Serializers/Deserializers/Deserializer.h Factories/RemoteNodeFactory.cpp Factories/RemoteNodeFactory.h Communication/Initializers/Initializer.cpp Communication/Initializers/Initializer.h Communication/Initializers/SocketInitializer.cpp Communication/Initializers/SocketInitializer.h Serializers/Connectors/Connector.cpp Serializers/Connectors/Connector.h Serializers/Connectors/HostConnector.cpp Serializers/Connectors/HostConnector.h Factories/SocketRemoteNodeFactory.cpp Factories/SocketRemoteNodeFactory.h Factories/NetworkManagerFactory.cpp Factories/NetworkManagerFactory.h)