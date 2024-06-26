#include <userver/utest/using_namespace_userver.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/components/component_list.hpp>
#include <userver/server/handlers/ping.hpp>
#include <userver/formats/json/value.hpp>
#include <userver/formats/json/serialize.hpp>
#include <userver/utils/log.hpp>
#include <userver/components/run.hpp>

#include <iostream>

using namespace userver;

class ApiKeyManager final : public server::handlers::HttpHandlerBase {
 public:
  static constexpr std::string_view kName = "api-key-manager";

  ApiKeyManager(const components::ComponentConfig& config,
                const components::ComponentContext& context)
      : HttpHandlerBase(config, context) {}

  std::string HandleRequestThrow(const server::http::HttpRequest& request,
                                 server::request::RequestContext&) const override {
    if (request.GetMethod() == server::http::HttpMethod::kPost) {
      return CreateApiKey(request);
    } else if (request.GetMethod() == server::http::HttpMethod::kGet) {
      return GetApiKey(request);
    } else if (request.GetMethod() == server::http::HttpMethod::kDelete) {
      return DeleteApiKey(request);
    }
    return "{}";
  }

 private:
  std::string CreateApiKey(const server::http::HttpRequest&) const {
    // Логика создания нового API-ключа
    formats::json::ValueBuilder response;
    response["status"] = "API key created successfully";
    return formats::json::ToString(response.ExtractValue());
  }

  std::string GetApiKey(const server::http::HttpRequest&) const {
    // Логика получения информации об API-ключе
    formats::json::ValueBuilder response;
    response["api_key"] = "example_key";
    return formats::json::ToString(response.ExtractValue());
  }

  std::string DeleteApiKey(const server::http::HttpRequest&) const {
    // Логика удаления API-ключа
    formats::json::ValueBuilder response;
    response["status"] = "API key deleted successfully";
    return formats::json::ToString(response.ExtractValue());
  }
};

void AppendComponentList(userver::components::ComponentList& component_list) {
  component_list.Append<server::handlers::Ping>()
                 .Append<ApiKeyManager>();
}

int main(int argc, char* argv[]) {
  try {
    const std::string config_path = "config/config.yaml";
    const std::optional<std::string> config_vars_path = std::nullopt;
    const std::optional<std::string> config_vars_override_path = std::nullopt;
    
    userver::components::ComponentList component_list;
    AppendComponentList(component_list);
    
    userver::components::Run(config_path, config_vars_path, config_vars_override_path, component_list);
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}