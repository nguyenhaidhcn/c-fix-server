/****************************************************************************
** Copyright (c) quickfixengine.org  All rights reserved.
**
** This file is part of the QuickFIX FIX Engine
**
** This file may be distributed under the terms of the quickfixengine.org
** license as defined by quickfixengine.org and appearing in the file
** LICENSE included in the packaging of this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** See http://www.quickfixengine.org/LICENSE for licensing information.
**
** Contact ask@quickfixengine.org if any conditions of this licensing are
** not clear to you.
**
****************************************************************************/

#ifdef _MSC_VER
#pragma warning( disable : 4503 4355 4786 )
#else
#include "config.h"
#endif

#include "Application.h"
#include "quickfix/Session.h"
#include "quickfix/fieldmap.h"
#include "quickfix/fix50sp2/MarketDataIncrementalRefresh.h"
#include "quickfix/fix50sp2/MarketDataRequest.h"

#include <fstream>

void Application::onLogon( const FIX::SessionID& sessionID ) 
{
	std::cout << std::endl << "Logon - " << sessionID << std::endl;
	sessions_.insert(sessions_.end(), sessionID);
}

void Application::onLogout( const FIX::SessionID& sessionID ) 
{	
	std::cout << std::endl << "Logout - " << sessionID << std::endl;
	sessions_.remove(sessionID);
}

void Application::toAdmin( FIX::Message& message, const FIX::SessionID& )
{
	std::cout << std::endl << "ADMIN OUT: " << message << std::endl;
}
void Application::fromAdmin( const FIX::Message& message, const FIX::SessionID& )
  throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon ) 
{
	std::cout << std::endl << "ADMIN IN: " << message << std::endl;
}
void Application::fromApp( const FIX::Message& message,
                           const FIX::SessionID& sessionID )
throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType )
{
	std::cout << std::endl << "IN: " << message << std::endl;
	crack( message, sessionID );
}

void Application::onMessage(const FIX50SP2::SecurityDefinitionRequest& message, const FIX::SessionID&)
{
	std::cout << std::endl << "SecurityDefinitionRequest: " << message << std::endl;
	FIX::Symbol symbol;
	FIX::SecurityExchange exch;
	FIX::SecurityType instrType;
	FIX50SP2::MarketDataRequest::NoRelatedSym grp;
	int numSym =  message.groupCount(FIX::FIELD::NoRelatedSym);
	for (int i = 1; i <= numSym; ++i)
	{
		message.getGroup(i, grp);
		grp.get(symbol);
		grp.get(exch);
		grp.get(instrType);

	}
}



void Application::toApp( FIX::Message& message, const FIX::SessionID& sessionID )
  throw( FIX::DoNotSend ) 
{
	std::cout << std::endl << "OUT: " << message << std::endl;
}


namespace FIX
{
  namespace FIELD
  {
	const int MinInc = 6350;
	const int MinBR = 6351;
	const int YTM = 6360;
	const int YTW = 6361;
  }
	DEFINE_QTY(MinInc);
	DEFINE_QTY(MinBR);
	DEFINE_PERCENTAGE(YTM);
	DEFINE_PERCENTAGE(YTW);
}



