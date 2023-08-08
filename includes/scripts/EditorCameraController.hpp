#pragma once

#include <scripting/Script.hpp>

namespace texplr {

class EditorCameraController : public virtual Script {
public:
    EditorCameraController(float mouseSensitivity, float moveSpeed);

    virtual void OnInit() override;
    virtual void OnAttach() override;
    virtual void OnUpdate(float deltaTime) override;

private:
    float m_mouseSensitivity;
    float m_moveSpeed;
};

} // namespace texplr
