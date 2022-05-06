/* -*- C++ -*- */

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

#ifndef ORDERMATCH_APPLICATION_H
#define ORDERMATCH_APPLICATION_H

#include <list>
#include <iostream>

#include "quickfix/Application.h"
#include "quickfix/MessageCracker.h"
#include "quickfix/Values.h"
#include "quickfix/Utility.h"
#include "quickfix/Mutex.h"
#include "quickfix/fix50sp2/SecurityDefinitionRequest.h"
#include "quickfix/fix50sp2/MarketDataRequest.h"

class Application
      : public FIX::Application,
        public FIX::MessageCracker
{
  // Application overloads
  void onCreate( const FIX::SessionID& ) {}
  void onLogon( const FIX::SessionID& sessionID );
  void onLogout( const FIX::SessionID& sessionID );
  void toAdmin( FIX::Message&, const FIX::SessionID& );
  void toApp( FIX::Message&, const FIX::SessionID& );
  void fromAdmin( const FIX::Message&, const FIX::SessionID& )
  throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon );
  void fromApp( const FIX::Message& message, const FIX::SessionID& sessionID )
  throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType );

public:

    void onMessage(const FIX50SP2::SecurityDefinitionRequest& message, const FIX::SessionID&);
    void onMessage(const FIX50SP2::MarketDataRequest& message, const FIX::SessionID&)
    {
		std::string msg = message.toString();
		std::cout << std::endl << "MarketDataRequest: " << message << std::endl;
		FIX::Symbol symbol;
		FIX::SecurityExchange exch;
		FIX::SecurityType instrType;
		FIX50SP2::MarketDataRequest::NoRelatedSym grp;

		bool hasGroups = message.hasGroup(1, grp);
		std::cout << std::endl << "hasGroups: " << hasGroups << std::endl;
		if (hasGroups == false) return;
		message.getGroup(1, grp);
		grp.get(symbol);
		grp.get(exch);
		grp.get(instrType);
		//FIX::NoRelatedSym numSym;
		//message.getField(numSym);
		//for (int i = 1; i <= numSym.getValue(); ++i)
		//{
		//	bool hasGroups =  message.hasGroup(i, grp);
		//	std::cout << std::endl << "hasGroups: " << hasGroups << std::endl;
		//	if (hasGroups == false) continue;
		//	message.getGroup(i, grp);
		//	grp.get(symbol);
		//	grp.get(exch);
		//	grp.get(instrType);

		//}
    }
private:
	std::list<FIX::SessionID> sessions_;
};

#endif
