#include "glog/logging.h"
#include<iostream>
#include <glog/raw_logging.h>
namespace GLOG::configure{
//封装
class glogcreate
{
public:
//配置glog
    glogcreate(char* program);
//析构释放内存
    ~glogcreate();

};
}//namespace GlOG::configur
