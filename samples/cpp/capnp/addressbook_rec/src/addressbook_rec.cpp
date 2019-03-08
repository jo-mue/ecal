/* ========================= eCAL LICENSE =================================
 *
 * Copyright (C) 2016 - 2019 Continental Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ========================= eCAL LICENSE =================================
*/

#include <ecal/ecal.h>
#include <ecal/msg/capnproto/subscriber.h>

#include <iostream>
#include <chrono>
#include <thread>

// capnp includes
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4100 4239)
#endif
#include "addressbook.capnp.h" 
#ifdef _MSC_VER
#pragma warning(pop)
#endif

void printAddressBook(capnp::MallocMessageBuilder& msg_)
{
  AddressBook::Reader addressBook = msg_.getRoot<AddressBook>();

  for (Person::Reader person : addressBook.getPeople())
  {
    std::cout << person.getName().cStr() << ": " << person.getEmail().cStr() << std::endl;
    for (Person::PhoneNumber::Reader phone : person.getPhones())
    {
      const char* typeName = "UNKNOWN";
      switch (phone.getType()) {
      case Person::PhoneNumber::Type::MOBILE: typeName = "mobile"; break;
      case Person::PhoneNumber::Type::HOME:   typeName = "home";   break;
      case Person::PhoneNumber::Type::WORK:   typeName = "work";   break;
      }
      std::cout << "  " << typeName << " phone: " << phone.getNumber().cStr() << std::endl;
    }
    Person::Employment::Reader employment = person.getEmployment();

    switch (employment.which())
    {
    case Person::Employment::UNEMPLOYED:
      std::cout << "  unemployed" << std::endl;
      break;
    case Person::Employment::EMPLOYER:
      std::cout << "  employer: "
        << employment.getEmployer().cStr() << std::endl;
      break;
    case Person::Employment::SCHOOL:
      std::cout << "  student at: "
        << employment.getSchool().cStr() << std::endl;
      break;
    case Person::Employment::SELF_EMPLOYED:
      std::cout << "  self-employed" << std::endl;
      break;
    }
  }
}

void OnAddressbook(const char* topic_name_, const capnp::MallocMessageBuilder& msg_, const long long time_)
{
  // print content
  std::cout << "topic name : " << topic_name_ << std::endl;
  std::cout << "time       : " << time_       << std::endl;
  std::cout << std::endl;
  printAddressBook(const_cast<capnp::MallocMessageBuilder&>(msg_));
  std::cout << std::endl;
}
  
int main(int argc, char **argv)
{
  // initialize eCAL API
  eCAL::Initialize(argc, argv, "addressbook subscriber");

  // set process state
  eCAL::Process::SetState(proc_sev_healthy, proc_sev_level1, "I feel good !");

  // create a subscriber (topic name "addressbook")
  eCAL::CCapnpSubscriber<capnp::MallocMessageBuilder> sub("addressbook");

  // add receive callback function (_1 = topic_name, _2 = msg, _3 = time)
  auto callback = std::bind(OnAddressbook, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  sub.AddReceiveCallback(callback);

  // enter main loop
  while (eCAL::Ok())
  {
    // sleep 500 ms
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }

  // finalize eCAL API
  eCAL::Finalize();
}
