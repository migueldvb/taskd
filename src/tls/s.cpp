#include <iostream>
#include <TLSServer.h>

int main (void)
{
  // This is a sample TLS 1.0 echo server, using X.509 authentication.
  TLSServer server;
  server.debug ();
  server.init ("pki/ca.cert.pem",      // CA
               "pki/server.crl.pem",   // CRL
               "pki/server.cert.pem",  // Cert
               "pki/server.key.pem");  // Key
  server.bind ("5556");
  server.listen ();

  for (;;)
  {
    TLSTransaction tx;
    server.accept (tx);

    std::string request;
    tx.recv (request);
    std::cout << request << "\n";
    tx.send (request);  // Echo back.
    tx.bye ();
  }

  return 0;
}
