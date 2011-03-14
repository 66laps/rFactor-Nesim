/*
 * This file is part of the rFactor-Nesim.
 *
 * Martin Galpin (m@66laps.com).
 *
 * Copyright(c) 2011 66laps Limited.
 *
 * This file may be licensed under the terms of of the
 * GNU General Public License Version 3 (the ``GPL'').
 *
 * Software distributed under the License is distributed
 * on an ``AS IS'' basis, WITHOUT WARRANTY OF ANY KIND, either
 * express or implied. See the GPL for the specific language
 * governing rights and limitations.
 *
 * You should have received a copy of the GPL along with this
 * program. If not, go to http://www.gnu.org/licenses/gpl.html
 * or write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef UDPSOCKET_HPP
#define UDPSOCKET_HPP

#include <WinSock.h>

/**
 * A basic wrapper for an asyncronous UDP socket.
 */
class UdpSocket
{
public:
    UdpSocket(const char* host, int port);
    ~UdpSocket(void);

    void Send(char* str, size_t length);
  
    void Open();
    void Close();
private:
    const char* mHost;
    int mPort;
    int mSocket;
    struct sockaddr_in mSocketAddress;
    WSADATA mWinsockData;
};

#endif // UDPSOCKET_HPP
