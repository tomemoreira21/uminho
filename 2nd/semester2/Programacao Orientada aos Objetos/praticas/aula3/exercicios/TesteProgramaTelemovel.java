public class TesteProgramaTelemovel {
    public static void main (String[] args) {
        // Criar telemóvel vazio
        Telemovel t1 = new Telemovel(
                "Samsung", 
                "Galaxy S23", 
                1080, 
                2400, 
                5000,      // armazenamento máximo de mensagens (bytes)
                100000,    // armazenamento máximo fotos + apps
                60000,     // armazenamento máximo fotos
                40000,     // armazenamento máximo apps
                0, 0, 0,   // espaço ocupado inicialmente
                0, 0,      // nFotosSave, nAppInstaladas
                new String[0], new String[0]  // arrays vazios
        );

        // Instalar apps
        t1.instalaApp("WhatsApp", 12000);
        t1.instalaApp("Instagram", 15000);
        t1.instalaApp("Spotify", 10000);

        // Receber mensagens
        t1.recebeMsg("Olá, tudo bem?");
        t1.recebeMsg("Esta é a segunda mensagem do telemóvel.");
        t1.recebeMsg("Mensagem de teste para validar armazenamento.");

        // Mostrar resultados
        System.out.println("Apps instaladas:");
        for (String app : t1.getNomeApp()) {
            System.out.println("- " + app);
        }
        System.out.println("Número de apps instaladas: " + t1.getnAppInstaladas());
        System.out.println("Espaço ocupado por apps: " + t1.getEspacoOcupadoApp() + " bytes");
        System.out.println("Tamanho médio das apps: " + t1.tamMedioApps() + " bytes");

        System.out.println("\nMensagens recebidas:");
        for (String msg : t1.getTexto()) {
            System.out.println("- " + msg);
        }

        String s = t1.maiorMsg();
        System.out.println("Maior mensagem: " + s + " (" + s.getBytes().length + " bytes)");
        System.out.println("Espaço ocupado por mensagens: " + t1.getEspacoOcupadoTexto() + " bytes");

        // Remover app
        t1.removeApp("Instagram", 15000);
        System.out.println("\nApós remover Instagram:");
        System.out.println("Número de apps instaladas: " + t1.getnAppInstaladas());
        System.out.println("Espaço ocupado por apps: " + t1.getEspacoOcupadoApp() + " bytes");

        // Testar espaço restante
        int novaAppSize = 20000;
        System.out.println("\nExiste espaço para app de " + novaAppSize + " bytes? " 
                + t1.existeEspaco(novaAppSize));
    }
}


