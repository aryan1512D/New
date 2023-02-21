#include <iostream>
#include rapidjson / document.h
#include rapidjson / prettywriter.h
#include rapidjson / writer.h

using namespace rapidjson;

void convertJSONtoXML(Value &value, XMLWriter &writer);

int main()
{
    const char *json = R"(
      {
        "person": {
          "name": "John Smith",
          "age": 20,
          "address": {
            "street": "123 Main Street",
            "city": "Abctown",
            "state": "XY",
            "zip": "1234"
          }
        }
      }
    )";

    Document doc;
    doc.Parse(json);

    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);
    writer.StartObject();

    convertJSONtoXML(doc, writer);

    writer.EndObject();
    std::cout << sb.GetString() << std::endl;
}

void convertJSONtoXML(Value &value, XMLWriter &writer)
{
    if (value.IsObject())
    {
        writer.StartObject();
        for (auto &member : value.GetObject())
        {
            writer.String(member.name.GetString());
            convertJSONtoXML(member.value, writer);
        }
        writer.EndObject();
    }
    else if (value.IsArray())
    {
        writer.StartArray();
        for (auto &item : value.GetArray())
        {
            convertJSONtoXML(item, writer);
        }
        writer.EndArray();
    }
    else if (value.IsString())
    {
        writer.String(value.GetString());
    }
    else if (value.IsNumber())
    {
        writer.Double(value.GetDouble());
    }
    else if (value.IsBool())
    {
        writer.Bool(value.GetBool());
    }
    else if (value.IsNull())
    {
        writer.Null();
    }
}