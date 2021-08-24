#define _SILENCE_ALL_CXX20_DEPRECATION_WARNINGS

//����漰����ַ���ȵ�����
#define __EA64__
//
// ida7.5�����ϵĲ��һ��Ҫ���������
// Ϊ�˱�֤�ϴ����ܹ����룬IDA���ǻ�֧��һЩ�Ͻṹ�壬��������IDA��ȫ�������ã��ᵼ��δ��������
// �����ȷ����û��ʹ��sdk�з����Ĵ���
//
#define NO_OBSOLETE_FUNCS

#include "./hexrays_sdk/include/hexrays.hpp"

struct plugin_ctx_t : public plugmod_t
{
    ~plugin_ctx_t()
    {
        term_hexrays_plugin();
    }
    virtual bool idaapi run(size_t) override;
};



//--------------------------------------------------------------------------
bool idaapi plugin_ctx_t::run(size_t)
{
    msg("hello world");
    
    return true;
}

//--------------------------------------------------------------------------
// Initialize the plugin.
static plugmod_t* idaapi init()
{
    if (!init_hexrays_plugin())
        return nullptr; // no decompiler
    const char* hxver = get_hexrays_version();
    msg("Hex-rays version %s has been detected, %s ready to use\n",
        hxver, PLUGIN.wanted_name);
    return new plugin_ctx_t;
}

//--------------------------------------------------------------------------
static const char comment[] = "whatever you want";

//--------------------------------------------------------------------------
//
//      PLUGIN DESCRIPTION BLOCK
//
//--------------------------------------------------------------------------
plugin_t PLUGIN =
{
  IDP_INTERFACE_VERSION,
  PLUGIN_MULTI|PLUGIN_UNL,//PLUGIN_UNL��������
  init,                 // initialize
  nullptr,
  nullptr,
  comment,              // long comment about the plugin
  nullptr,              // multiline help about the plugin
  "whatever you want", // ��Edit->Plugins����ʵ������
  nullptr,              // �ȼ�
};
