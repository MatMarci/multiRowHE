#include <Config.h>

void Config::setOtherInitValues(){
    this->AIR_VELOCITY_BEFORE_HE = (this->AIR_FLOW[0]/3600)/(this->HE_HEIGHT*this->HE_LENGTH);
    this->AIR_VELOCITY_BEFORE_HE = (this->AIR_FLOW[0]/3600)/(this->HE_HEIGHT*this->HE_LENGTH);
    this->AIR_FLOW_PER_AREA = this->AIR_FLOW[0] / this->CONTROL_AREAS / this->TUBES_IN_ROW;
    this->WATER_FLOW_PER_ROW = this->WATER_FLOW[0]/(this->ROWS);
    this->WATER_FLOW_PER_TUBE = this->WATER_FLOW_PER_ROW/this->TUBES_IN_ROW;
    this->AREA_TUBE_LENGTH = this->HE_LENGTH/this->CONTROL_AREAS; //he HeatExchanger
    this->FINS_PER_AREA = this->AREA_TUBE_LENGTH/this->FIN_PITCH;
    this->INNER_TUBE_DIAM = this->OUTER_TUBE_DIAM - (2 * this->TUBE_WALL_THICK);
}
