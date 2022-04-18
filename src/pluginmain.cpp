#define _SILENCE_ALL_CXX20_DEPRECATION_WARNINGS

//����漰����ַ���ȵ����⣬��ida64.exe�͵ü�����꣬ida32.exe����
#define __EA64__

//
// ida7.5�����ϵĲ��һ��Ҫ���������
// Ϊ�˱�֤�ϴ����ܹ����룬IDA���ǻ�֧��һЩ�Ͻṹ�壬��������IDA��ȫ�������ã��ᵼ��δ��������
// �����ȷ����û��ʹ��sdk�з����Ĵ���
//
#define NO_OBSOLETE_FUNCS
#include <hexrays_sdk/include/hexrays.hpp>
#include <optional>
#include <format>

ssize_t idaapi ui_hook(void* user_data, int notification_code, va_list va);

struct plugin_ctx_t : public plugmod_t {
  plugin_ctx_t() {}
  virtual bool idaapi run(size_t) override;
  std::optional<qstring> get_ea_comment(ea_t ea) {
    qstring cmt;
    get_cmt(&cmt, ea, 0);
    if (cmt.empty()) {
      get_cmt(&cmt, ea, 1);
      if (cmt.empty())
        return std::nullopt;
      else
        return cmt;
    } else
      return cmt;
  }
  void show_comment_list();

    ~plugin_ctx_t() {
    unhook_from_notification_point(HT_UI, ui_hook);
    term_hexrays_plugin();
    }

};
//--------------------------------------------------------------------------
bool idaapi plugin_ctx_t::run(size_t) {
  hook_to_notification_point(HT_UI, ui_hook);
  show_comment_list();
  
  return true;
}

//--------------------------------------------------------------------------
// Initialize the plugin.
static plugmod_t* idaapi init() {
  if (!init_hexrays_plugin()) {
    return nullptr;  // plugin will not be loaded
  }
  const char* hxver = get_hexrays_version();
  
  msg(std::format("[{}]make sure your IDA version not lower than 7.5\n", PLUGIN.wanted_name).c_str());
  return new plugin_ctx_t;
}

//--------------------------------------------------------------------------
//
//      PLUGIN DESCRIPTION BLOCK
//
//--------------------------------------------------------------------------
plugin_t PLUGIN = {
    IDP_INTERFACE_VERSION,
#ifdef DEBUG
    PLUGIN_MULTI |
        PLUGIN_UNL,  // PLUGIN_UNL�������ڲ��run�����õ�ʱ���Զ�unload,�ٴ�run��ʱ��ida��ȥ�������¼����±����DLL
#else
    PLUGIN_MULTI,
#endif  // DBG
    init,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    "comment_list",
    nullptr,
};

/*
shift+;  ��unrepeatable cmt
; ��repeatable cmt

shift+;�Ḳ��;

���������unrep��,Ӧ����ʾunrep,û��unrep����ʾrep

������˶�����;��ֱ��ע�͵�
�������һ����ַ�кܶ���(������ͷ),;�����Ȼ�ע���ڿ�ͷ,����shift+;����ע��������λ��
*/
void plugin_ctx_t::show_comment_list() {

    
    
    
}

ssize_t ui_hook(void* user_data, int notification_code,
                              va_list va) {

    
  return 0;
}