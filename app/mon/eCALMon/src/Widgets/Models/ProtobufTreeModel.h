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

#include <CustomQt/QAbstractTreeModel.h>
#include <CustomQt/QAbstractTreeItem.h>

#include <QObject>
#include <QModelIndex>

#include <map>

#include "ProtobufTreeItem.h"

#include <ecal/protobuf/ecal_proto_hlp.h>

class ProtobufTreeModel : public QAbstractTreeModel
{
  Q_OBJECT

public:

  enum class Columns : int
  {
    FIELD_NAME,
    NUMBER,
    FIELD_RULE,
    TYPE_NAME,
    VALUE,

    COLUMN_COUNT
  };

  ProtobufTreeModel(QObject *parent = nullptr);
  ~ProtobufTreeModel();

  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

  int mapColumnToItem(int model_column, int tree_item_type) const override;

  void setRoot(QAbstractTreeItem* root) override;

  bool displayBlobs() const;

  void setDisplayBlobs(bool enabled);

public slots:
  void setMessage(const google::protobuf::Message& message);

private:
  std::map<Columns, QString> column_labels_ =
  {
    { Columns::FIELD_NAME, "Field" },
    { Columns::NUMBER,     "Number" },
    { Columns::FIELD_RULE, "Rule" },
    { Columns::TYPE_NAME,  "Type" },
    { Columns::VALUE,      "Value" },
  };

  std::map<Columns, int> item_column_mapping_ =
  {
    { Columns::FIELD_NAME, (int)ProtobufTreeItem::Columns::FIELD_NAME },
    { Columns::NUMBER,     (int)ProtobufTreeItem::Columns::NUMBER },
    { Columns::FIELD_RULE, (int)ProtobufTreeItem::Columns::FIELD_RULE },
    { Columns::TYPE_NAME,  (int)ProtobufTreeItem::Columns::TYPE},
    { Columns::VALUE,      (int)ProtobufTreeItem::Columns::VALUE },
  };

  bool display_blobs_;

};
