set(project nms)

set(${project}_files
    ${CMAKE_CURRENT_SOURCE_DIR}/AbstractClientInitializer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AbstractInitializer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BoolImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BoolWrapper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CharImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CharWrapper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ClientConfiguration.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ClientIdentity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Connection.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ConnectionThread.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DefaultSerializableObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DoubleImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DoubleWrapper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DynamicClientInitializer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FloatImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FloatWrapper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IntImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IntWrapper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libnms.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LocalTCPClient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LocalTCPClientFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LongImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LongWrapper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Message.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MessageImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ObjectFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Parameter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ParameterImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PnmsDynamicClient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PnmsDynamicClientImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PnmsGenericClientImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PnmsNetwork.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PnmsSecureClient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PnmsSecureClientImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PnmsTCPSocket.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PnmsUDPSocket.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Receiver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SecureClientInitializer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SerializableObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StringImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StringWrapper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Subscription.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TcpThread.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Transporter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TransporterImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/xml_handler.cpp
)

add_library(${project} SHARED ${${project}_files} )

target_link_libraries(${project} pnms-common)
