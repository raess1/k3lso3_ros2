#include "moteus_pcan/moteus_pcan_controller.h" 
#include "moteus_pcan/utils.h"

MoteusPcanController::MoteusPcanController(const MoteusInterfaceMotorsMap& interface_motors_map)
    : initialized(false)
    , interface_motors_map(interface_motors_map)
{
    for (auto const& [interface, ids] : interface_motors_map)
    {
        interfaces.push_back(std::make_shared<MoteusPcanInterface>(interface, ids));
        if(!interfaces.back()->is_initialized()){
            std::cerr << "[ERROR]: " << "Unable to initialize CAN interface: " << interface << std::endl;
            return;
        }
        for(const auto& [id, motor]: interfaces.back()->motors){
            if(!KEY_IN_MAP(id, motors)){
                motors[id] = motor;
            }else{
                std::cerr << "[ERROR]: " << "Mutiple definition of ID: " << id << std::endl;
                return;
            }
        }
    }
    initialized = true;
    for(const auto& interface: interfaces){
        interface->start();
    }
    return;
}

MoteusPcanController::~MoteusPcanController(){
    for(const auto& interface: interfaces){
        interface->stop();
    }
}

bool MoteusPcanController::is_initialized(){
    return initialized;
}

bool MoteusPcanController::set_torque_ena(bool torque_ena){
    for(const auto& [id, motor]: motors){
        motor->set_torque_ena(torque_ena);
    }
    return true;
}

bool MoteusPcanController::set_torque_ena(bool torque_ena, int id){
    if(KEY_IN_MAP(id, motors)){
        motors[id]->set_torque_ena(torque_ena);
    }else{
        std::cerr << "[ERROR]: " << "ID not defined: " << id << std::endl;
        return false;
    }
    return true;
}

bool MoteusPcanController::set_torque_ena(bool torque_ena, std::vector<int> ids){
    for(const auto& id: ids){
        if(KEY_IN_MAP(id, motors)){
            motors[id]->set_torque_ena(torque_ena);
        }else{
            std::cerr << "[ERROR]: " << "ID not defined: " << id << std::endl;
            return false;
        }   
    }
    return true;
}

bool MoteusPcanController::set_command(int id, float position, float velocity, float fftorque, float kp_scale, float kd_scale){
    if(KEY_IN_MAP(id, motors)){
        motors[id]->set_commands(position, velocity, fftorque, kp_scale, kd_scale);
    }else{
        std::cerr << "[ERROR]: " << "ID not defined: " << id << std::endl;
        return false;
    }
    return true;
}

bool MoteusPcanController::set_command(int id, float position, float velocity, float fftorque){
    if(KEY_IN_MAP(id, motors)){
        motors[id]->set_commands(position, velocity, fftorque);
    }else{
        std::cerr << "[ERROR]: " << "ID not defined: " << id << std::endl;
        return false;
    }
    return true;
}

bool MoteusPcanController::set_command(int id, float position, float velocity){
    if(KEY_IN_MAP(id, motors)){
        motors[id]->set_commands(position, velocity);
    }else{
        std::cerr << "[ERROR]: " << "ID not defined: " << id << std::endl;
        return false;
    }
    return true;
}

bool MoteusPcanController::set_command(int id, float position){
    if(KEY_IN_MAP(id, motors)){
        motors[id]->set_commands(position);
    }else{
        std::cerr << "[ERROR]: " << "ID not defined: " << id << std::endl;
        return false;
    }
    return true;
}

bool MoteusPcanController::set_command(std::vector<int> ids, std::vector<float> position, std::vector<float> velocity, 
                                       std::vector<float> fftorque, std::vector<float> kp_scale, std::vector<float> kd_scale){
    for(size_t i=0; i<ids.size(); i++){
        if(KEY_IN_MAP(ids[i], motors)){
            motors[ids[i]]->set_commands(position[i], velocity[i], fftorque[i], kp_scale[i], kd_scale[i]);
        }else{
            std::cerr << "[ERROR]: " << "ID not defined: " << ids[i] << std::endl;
            return false;
        }   
    }
    return true;
}

bool MoteusPcanController::set_command(std::vector<int> ids, std::vector<float> position, std::vector<float> velocity, 
                                       std::vector<float> fftorque){
    for(size_t i=0; i<ids.size(); i++){
        if(KEY_IN_MAP(ids[i], motors)){
            motors[ids[i]]->set_commands(position[i], velocity[i], fftorque[i]);
        }else{
            std::cerr << "[ERROR]: " << "ID not defined: " << ids[i] << std::endl;
            return false;
        }   
    }
    return true;
}

bool MoteusPcanController::set_command(std::vector<int> ids, std::vector<float> position, std::vector<float> velocity){
    for(size_t i=0; i<ids.size(); i++){
        if(KEY_IN_MAP(ids[i], motors)){
            motors[ids[i]]->set_commands(position[i], velocity[i]);
        }else{
            std::cerr << "[ERROR]: " << "ID not defined: " << ids[i] << std::endl;
            return false;
        }   
    }
    return true;
}

bool MoteusPcanController::set_command(std::vector<int> ids, std::vector<float> position){
    for(size_t i=0; i<ids.size(); i++){
        if(KEY_IN_MAP(ids[i], motors)){
            motors[ids[i]]->set_commands(position[i]);
        }else{
            std::cerr << "[ERROR]: " << "ID not defined: " << ids[i] << std::endl;
            return false;
        }   
    }
    return true;
}

std::vector<int> MoteusPcanController::get_freqs(){
    std::vector<int> freqs;
    for(const auto& interface: interfaces){
        freqs.push_back(interface->freq);
    }
    return freqs;
}
