#include <YutsuOS/macros.h>
#include <YutsuOS/yutsh/builtin.h>

#include <YutsuOS/core/keyboard.h>

u8 yutsu_builtin_qwerty(const Array YUTSUOS_UNUSED *args)
{
    yutsu_set_keyboard_layout(LAYOUT_QWERTY);
    return YUTSUOS_SUCCESS;
}
