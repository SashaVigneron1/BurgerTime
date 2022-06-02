#include "PeakAEnginePCH.h"
#include "JsonParser.h"

#include <fstream>
#include <istreamwrapper.h>

#include "rapidjson.h"
#include "StringBuffer.h"
#include "Writer.h"

JsonParser::JsonParser(const std::string& filePath)
	: m_FilePath{filePath}
	, m_pDocument{new rapidjson::Document{}}
{
	LoadDocument();
}

JsonParser::~JsonParser()
{
	delete m_pDocument;
}

void JsonParser::LoadDocument()
{
	std::ifstream inputFileStream{ m_FilePath };
	{
		using namespace rapidjson;

		// Write Json Data into doc
		IStreamWrapper isw{ inputFileStream };

		m_pDocument->ParseStream(isw);

		StringBuffer buffer{};
		Writer<StringBuffer> writer{ buffer };
		m_pDocument->Accept(writer);

		// ErrorCheck
		if (m_pDocument->HasParseError())
		{
			std::cerr << "Error  : " << m_pDocument->GetParseError() << '\n'
				<< "Offset : " << m_pDocument->GetErrorOffset() << '\n';
		}
	}
}
