#include<google_logger.h>
#include "glog/logging.h"
#define LOGDIR "/home/mayuqi/桌面/vision_quickdemo/logs"
namespace GLOG::configure{
//配置实现
glogcreate::glogcreate(char* program){
    google::InitGoogleLogging(program);//初始化
    FLAGS_alsologtostderr=true;
    FLAGS_colorlogtostderr=true;  //设置输出到屏幕的日志显示相应的颜色
    google::SetLogDestination(google::INFO,LOGDIR"/INFO_");//设置info的储存路径和前缀
    google::SetLogDestination(google::ERROR,LOGDIR"/ERROR_");
    google::SetLogDestination(google::WARNING,LOGDIR"/WARNIN_");
    FLAGS_logbufsecs=0;//缓冲日志输出，立即输出
    FLAGS_max_log_size=50;//日志最大为50mb
    google::InstallFailureSignalHandler();
    }
//析构实现
glogcreate::~glogcreate(){
        google::ShutdownGoogleLogging();
    }
}


