#include "../include/VkApi.h"

VkApi::VkApi()
    : session("api.vk.com", 443, new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "", "",
                                        "", Poco::Net::Context::VERIFY_NONE, 9,
                                        false,
                                        "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH")), request(Poco::Net::HTTPMessage::HTTP_1_1) {
    request.setMethod(Poco::Net::HTTPRequest::HTTP_GET);
}

Poco::JSON::Object::Ptr VkApi::executeMethod(
    const std::string& method, const Poco::URI::QueryParameters& params) {
    uri = "https://api.vk.com/method/" + method;
    uri.setQueryParameters(params);
    request.setURI(uri.toString());
    session.sendRequest(request);
    return parser.parse(session.receiveResponse(response))
        .extract<Poco::JSON::Object::Ptr>();
}