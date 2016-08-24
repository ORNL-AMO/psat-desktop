#include <node.h>
#include <initializer_list>

#include "../amo-library/Pump.h"
#include "../amo-library/calculator/PumpEfficiency.h"
#include "../amo-library/calculator/OptimalPumpEfficiency.h"
#include "../amo-library/calculator/MotorRatedPower.h"
#include "../amo-library/calculator/OptimalMotorRatedPower.h"
#include "../amo-library/calculator/MotorShaftPower.h"
#include "../amo-library/calculator/OptimalMotorShaftPower.h"
#include "../amo-library/calculator/PumpShaftPower.h"
#include "../amo-library/calculator/OptimalPumpShaftPower.h"
#include "../amo-library/calculator/MotorEfficiency.h"
#include "../amo-library/calculator/OptimalMotorEfficiency.h"
#include "../amo-library/calculator/MotorPowerFactor.h"
#include "../amo-library/calculator/OptimalMotorPowerFactor.h"
#include "../amo-library/calculator/MotorCurrent.h"
#include "../amo-library/calculator/OptimalMotorCurrent.h"
#include "../amo-library/calculator/MotorPower.h"
#include "../amo-library/calculator/OptimalMotorPower.h"
#include "../amo-library/AnnualEnergy.h"
#include "../amo-library/AnnualCost.h"
#include "../amo-library/AnnualSavingsPotential.h"
#include "../amo-library/OptimizationRating.h"

using namespace v8;

Local<Array> r;
Isolate* iso;

void set(std::initializer_list <double> args) {
  for (auto d : args) {
    r->Set(r->Length(),Number::New(iso,d));
  }
}
void Results(const FunctionCallbackInfo<Value>& args) {
  iso = args.GetIsolate();
  r = Array::New(iso);
  set({
    (new PumpEfficiency(0,0,0,0))->calculate(),
    (new OptimalPumpEfficiency(Pump::Style::END_SUCTION_SLURRY,0,0,0,0,0,Pump::Speed::FIXED_SPECIFIC_SPEED))->calculate(),
    (new MotorRatedPower(0))->calculate(),
    (new OptimalMotorRatedPower(0,0))->calculate(),
    (new MotorShaftPower(0,0))->calculate(), 
    (new OptimalMotorShaftPower(0,Pump::Drive::DIRECT_DRIVE))->calculate(),
    (new PumpShaftPower(0,Pump::Drive::DIRECT_DRIVE))->calculate(),
    (new OptimalPumpShaftPower(0,0,0,0))->calculate(),
    (new MotorEfficiency(0,0,Motor::EfficiencyClass::STANDARD,0,FieldData::LoadEstimationMethod::POWER,0,0,0))->calculate(),
    (new OptimalMotorEfficiency(0,0))->calculate(),
    (new MotorPowerFactor(0,0,Motor::EfficiencyClass::STANDARD,0,FieldData::LoadEstimationMethod::POWER,0,0,0))->calculate(),
    (new OptimalMotorPowerFactor(0,0))->calculate(),
    (new MotorCurrent(0,0,0))->calculate(),
    (new OptimalMotorCurrent(0,0))->calculate(),
    (new MotorPower(0,0,0,0))->calculate(),
    (new OptimalMotorPower(0,0))->calculate(),
    (new AnnualEnergy(0,0))->calculate(),
    (new AnnualEnergy(0,0))->calculate(),
    (new AnnualCost(0,0))->calculate(),
    (new AnnualCost(0,0))->calculate(),
    -1,
    (new AnnualSavingsPotential(0,0))->calculate(),
    args[0]->ToObject()->Get(String::NewFromUtf8(iso,"stages"))->NumberValue(), 
    (new OptimizationRating(0,0))->calculate()
  });
  args.GetReturnValue().Set(r);
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "results", Results);    
}

NODE_MODULE(bridge, init)

