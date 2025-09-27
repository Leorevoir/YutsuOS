#include <YutsuOS/core/keyboard.h>
#include <YutsuOS/macros.h>
#include <YutsuOS/yutsh/builtin.h>

u8 yutsu_builtin_azerty(const Array YUTSUOS_UNUSED *args)
{
    yutsu_set_keyboard_layout(LAYOUT_AZERTY);
    return YUTSUOS_SUCCESS;
}
