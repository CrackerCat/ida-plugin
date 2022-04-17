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

// IDA�ڲ��õ����֣�ʶ��ÿ��UI������,ǰ�����������IDA���Ƽ�����
#define action_internal_name_1 "example::name"

//������Ҽ���ʾ���û�������
#define action_show_name_1 "example"

ssize_t idaapi ui_hook(void* user_data, int notification_code, va_list va) {
  if (notification_code == ui_populating_widget_popup) {
    TWidget* view = va_arg(va, TWidget*);
    if (get_widget_type(view) == BWN_DISASM) {
      TPopupMenu* p = va_arg(va, TPopupMenu*);
      attach_action_to_popup(view, p, action_internal_name_1, nullptr,
                             SETMENU_FIRST);
    }
  }

  return false;
}

struct example_action : public action_handler_t {
  // action�����������߼�
  virtual int idaapi activate(action_activation_ctx_t* ctx) override {
    msg("hello world");
    return true;
  }

  virtual action_state_t idaapi update(action_update_ctx_t* ctx) override {
    // AST_DISABLEѡ��Ļ�action���ǻ�ɫ���޷���
    return AST_ENABLE_ALWAYS;
  }
};

example_action action1;
struct plugin_ctx_t : public plugmod_t {
  plugin_ctx_t() {
    register_action(
        ACTION_DESC_LITERAL_PLUGMOD(action_internal_name_1,  // action name
                                    action_show_name_1,      // show name
                                    &action1, this, nullptr, nullptr, -1));

    hook_to_notification_point(HT_UI, ui_hook);
  }
  ~plugin_ctx_t() {
    unregister_action(action_internal_name_1);
    unhook_from_notification_point(HT_UI, ui_hook);
    term_hexrays_plugin();
  }
  virtual bool idaapi run(size_t) override;
};

//--------------------------------------------------------------------------
bool idaapi plugin_ctx_t::run(size_t) {
  msg("hello world");

  return true;
}

//--------------------------------------------------------------------------
// Initialize the plugin.
static plugmod_t* idaapi init() {
  if (!init_hexrays_plugin()) return nullptr;  // no decompiler
  const char* hxver = get_hexrays_version();
  msg("Hex-rays version %s has been detected, %s ready to use\n", hxver,
      PLUGIN.wanted_name);
  return new plugin_ctx_t;
}

//--------------------------------------------------------------------------
static const char comment[] = "whatever you want";

//--------------------------------------------------------------------------
//
//      PLUGIN DESCRIPTION BLOCK
//
//--------------------------------------------------------------------------
plugin_t PLUGIN = {
    IDP_INTERFACE_VERSION,
    PLUGIN_MULTI | PLUGIN_UNL,  // PLUGIN_UNL�������ԣ�runһ�ξ��Զ�ж�صĹ���
    init,                       // initialize
    nullptr,
    nullptr,
    comment,              // long comment about the plugin
    nullptr,              // multiline help about the plugin
    "whatever you want",  // ��Edit->Plugins����ʾ������
    nullptr,              // �ȼ�
};
