#pragma once

#include <core/Script.hpp>

namespace texplr {

class PlanetScript : public virtual Script {
public:
    virtual void OnInit() override;
    virtual void OnAttach() override;
    virtual void OnUpdate(float deltaTime) override;
};

} // namespace texplr
