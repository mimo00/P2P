cmake_minimum_required(VERSION 3.12)
project(P2P)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(P2P main.cpp NetworkManager.cpp NetworkManager.h RemoteNode.cpp RemoteNode.h Tasks/Task.cpp Tasks/Task.h Stoppable.cpp Stoppable.h Receiver.cpp Receiver.h Sender.cpp Sender.h Tasks/ReceiveKnownNodesTask.cpp Tasks/ReceiveKnownNodesTask.h Serializers/CommuniqueSerializer.cpp Serializers/CommuniqueSerializer.h Packages/Package.cpp Packages/Package.h Packages/ListOfFilesPackage.cpp Packages/ListOfFilesPackage.h Tasks/SenderTasks/SendFilesListRequest.cpp Tasks/SenderTasks/SendFilesListRequest.h Tasks/SenderTasks/SenderTask.cpp Tasks/SenderTasks/SenderTask.h Communication/Client.cpp Communication/Client.h Serializers/ReceiverDeserializer.cpp Serializers/ReceiverDeserializer.h OperationCode.cpp OperationCode.h Tasks/SenderTasks/SendFilesList.cpp Tasks/SenderTasks/SendFilesList.h Serializers/FilesListSerializer.cpp Serializers/FilesListSerializer.h)