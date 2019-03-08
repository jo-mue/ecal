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

#pragma once

#include "CustomQt/QAbstractTreeItem.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4146 4800)
#endif
#include "ecal/pb/service.pb.h"
#ifdef _MSC_VER
#pragma warning(pop)
#endif

class ServiceTreeItem :
  public QAbstractTreeItem
{
public:

  enum class Columns : int
  {
    RCLOCK,
    HNAME,
    PNAME,
    UNAME,
    PID,
    SNAME,
    TCP_PORT,
    MNAME,
    REQ_TYPE,
    RESP_TYPE,
    CALL_COUNT,
  };

  ServiceTreeItem();
  ServiceTreeItem(const eCAL::pb::Service& service, const eCAL::pb::Method& method);

  ~ServiceTreeItem();

  QVariant data(int column, Qt::ItemDataRole role = Qt::ItemDataRole::DisplayRole) const;

  QVariant data(Columns column, Qt::ItemDataRole role = Qt::ItemDataRole::DisplayRole) const;

  int type() const;

  std::string identifier() const;
  static std::string generateIdentifier(const eCAL::pb::Service& service, const eCAL::pb::Method& method);

  void update(const eCAL::pb::Service& service, const eCAL::pb::Method& method);

private:
  eCAL::pb::Service service_;
  eCAL::pb::Method  method_;
  std::string identifier_;
};

