#ifndef SAFE_DELETE
#define SAFE_DELETE(x)  do { if(x != NULL) { delete x; } x = NULL; } while(0)
#endif

#ifndef BEGIN_NAMESPACE
#define BEGIN_NAMESPACE1(ns1) namespace ns1 {
#define BEGIN_NAMESPACE2(ns1, ns2) namespace ns1 { namespace ns2 {
#define BEGIN_NAMESPACE3(ns1, ns2, ns3) namespace ns1 { namespace ns2 { namespace ns3 {
#define BEGIN_NAMESPACE4(ns1, ns2, ns3, ns4) namespace ns1 { namespace ns2 { namespace ns3 { namespace ns4 {

#define END_NAMESPACE1(ns1) }
#define END_NAMESPACE2(ns1, ns2) } }
#define END_NAMESPACE3(ns1, ns2, ns3) } } }
#define END_NAMESPACE4(ns1, ns2, ns3, ns4) } } } }

#define BEGIN_NAMESPACE
#define END_NAMESPACE
#endif

#ifndef BEGIN_NAMESPACE_IMESH_UI
  #define BEGIN_NAMESPACE_IMESH_UI namespace IMesh { namespace UI {
#endif

#ifndef END_NAMESPACE_IMESH_UI
  #define END_NAMESPACE_IMESH_UI } }
#endif