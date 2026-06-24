# Análise de Usabilidade

**Link Figma:** <https://www.figma.com/proto/JWAVZI7JquLQLKYSJt3iYL/Prot%C3%B3tipo-Trabalho-Pratico?node-id=5-137&t=2AlH8lWBqfppNgJL-1&scaling=min-zoom&content-scaling=fixed&page-id=0%3A1&starting-point-node-id=195%3A107>

---

## Introdução

Com o objetivo de desenhar uma interface que respondesse às necessidades dos utilizadores, recorreu-se a um conjunto de elementos e decisões de design adaptados a cada perfil definido. Para os perfis 1 e 2 foi desenvolvida uma interface orientada para a análise de dados, com suporte a exportações, gráficos, tabelas com valores concretos e piecharts. O perfil 3, por se tratar de uma utilizadora com um contexto diferente, exigiu uma atenção especial, optando-se por uma linguagem mais clara e acessível, com recurso a dados concretos, factsheets e cards simplistas.

---

## Heurísticas de Nielsen

Esta secção apresenta uma breve análise de usabilidade da interface proposta, descrevendo de que forma as guidelines e heurísticas de Nielsen foram tidas em consideração durante o processo de design.

### 1. Visibilidade do estado do sistema

A interface comunica bem o estado atual através do item ativo na barra lateral (ex: "Países" destacado a azul com borda lateral), do rasto de navegação "Países > Portugal" que indica onde o utilizador está, e dos valores numéricos nos cards que refletem os dados do país selecionado. O utilizador sabe sempre em que secção se encontra e que dados está a visualizar.

### 2. Correspondência entre o sistema e o mundo real

A linguagem usada é acessível e próxima do utilizador, por exemplo termos como "Impacto na vida das pessoas", "Escolas renovadas", "Habitações com apoio" em vez de terminologia técnica burocrática. As bandeiras dos países e os emojis ilustrativos nos cards reforçam a ligação ao mundo real e tornam a informação mais imediata e reconhecível.

### 3. Controlo e liberdade do utilizador

A interface disponibiliza botões como “Voltar” e “Desfazer”, que permitem corrigir rapidamente ações feitas por engano. A barra lateral também facilita o regresso ao estado inicial, garantindo que o utilizador mantém sempre o controlo sobre a navegação. Além disso, o facto da interface ser simples e intuitiva dá ao utilizador uma sensação de controle sobre as ações, fazendo com que não pense que vai fazer algo de errado.

### 4. Consistência e normas

A barra lateral mantém-se sempre no mesmo lugar e a cor azul aparece de forma coerente para identificar elementos ativos e valores relevantes. A estrutura de cada página segue sempre o mesmo padrão, o que torna a navegação previsível e familiar para quem usa a interface.

### 5. Prevenção de erros

A interface disponibiliza filtros com opções pré-definidas em vez de campos de texto livre, eliminando a possibilidade de o utilizador introduzir valores inválidos ou inexistentes, prevenindo assim erros antes de acontecerem. A simplicidade e intuitividade da interface também tomam peso na prevenção de erros. Uma interface que seja simples e intuitiva de usar leva a que os seus utilizadores cometam menos erros.

### 6. Reconhecer em vez de recordar

Tudo o que o utilizador precisa está à sua vista: os nomes dos países, os valores dos indicadores e a legenda de cores junto aos cards. Em nenhum momento é exigido ao utilizador que se lembre de algo que viu num ecrã anterior para conseguir interpretar a informação atual.

### 7. Flexibilidade e eficiência de utilização

A barra lateral permite ao utilizador experiente saltar diretamente para qualquer secção sem seguir um fluxo linear, acelerando assim a interação para um utilizador mais experiente. Além disso, estão presentes em certos cards da interface um botão "Ver mais" que permite um transição direta desses cards para o menu relativo à informação que apresentam.

### 8. Desenho estético e minimalista

O layout é limpo, com fundo neutro e sem decoração desnecessária. Os emojis nos cards têm função ilustrativa clara. Cada elemento presente na interface serve um propósito, sem sobrecarregar o utilizador com informação irrelevante.

### 9. Ajudar os utilizadores a reconhecer, diagnosticar e recuperar de erros

A interface apresenta mensagens de erro em linguagem simples e direta, identificando o problema e oferecendo uma solução. Por exemplo, ao exportar o gráfico de barras presente na página inicial, é apresentado um aviso claro com a descrição do erro e as opções de tentar novamente ou fechar.

### 10. Ajuda e documentação

O funcionamento da interface é simples e intuitivo, não sendo necessária documentação ou qualquer tipo de explicação adicional, podendo ainda assim vir a ser implementada numa segunda fase caso se revele necessário. Um utilizador sem experiência prévia consegue navegar e interpretar a informação sem dificuldade.

---

## Perfis de Utilizador

Esta secção descreve de que forma a interface responde às necessidades dos perfis de utilizador definidos.

### Perfil 1 — Helena Vasconcelos

Tendo em conta o perfil de Helena Vasconcelos, analista de políticas públicas especializada na monitorização da transparência dos fundos e no acompanhamento do cumprimento dos marcos definidos pela Comissão Europeia, a secção “Marcos e Metas” foi desenvolvida para facilitar a análise detalhada das medidas e permitir uma verificação clara do progresso e da responsabilização institucional.

O elemento central da página é a tabela “Marcos e Metas por medida”, que apresenta informação estruturada sobre cada medida associada aos planos nacionais. Nesta tabela é possível visualizar dados como o país, a designação da medida, o tipo de ação (reforma ou investimento), o estado de cumprimento, o respetivo progresso e em que pilares esta incide. Com as opções de filtro por país, tipo de medida, estado e pilar a Helena pode isolar rapidamente áreas específicas de interesse. Por exemplo, consultar medidas relacionadas com a digitalização ou com a transição verde, facilitando o acesso a metas específicas por setor.

Um dos aspetos mais relevantes para este perfil é a possibilidade de abrir uma janela de detalhe ao selecionar uma medida específica. Esta janela apresenta um resumo da medida, que inclui um histórico resumido de revisões do plano, que permite perceber de forma imediata como essa medida tem vindo a evoluir longo do tempo. Caso a Helena necessite de uma análise mais aprofundada, existe um botão que expande a visualização para mostrar o histórico completo de revisões, o que reforça a ideia transparência e permite identificar alterações, atualizações ou ajustes realizados pelas entidades responsáveis. Esta funcionalidade responde diretamente à sua necessidade de acompanhar a evolução e revisão dos planos públicos, que constitui um elemento essencial para a monitorização da responsabilização política.

Abaixo da tabela encontra-se um gráfico circular acompanhado de indicadores de progresso, que apresenta o número total de medidas monitorizadas, a sua distribuição por pilar estratégico e a taxa de progresso associada a cada pilar. Esta figura oferece uma leitura rápida do estado geral de implementação das políticas, permitindo identificar facilmente as áreas com maior ou menor nível de execução.

Falando agora de toda a interface, outro aspeto particularmente relevante para este perfil é a existência de um menu de exportação associado a todas as tabelas e gráficos presentes na interface, identificado por um ícone com três linhas. Ao clicar neste ícone, surge um pequeno menu com as opções de exportação em diferentes formatos. Esta funcionalidade responde diretamente à necessidade da Helena de trabalhar os dados externamente em formatos editáveis.

Concluindo, a interface apresenta a informação de forma clara e estruturada, permitindo à Helena acompanhar facilmente o progresso das medidas e o cumprimento dos marcos estabelecidos. Com tabelas detalhadas, filtros intuitivos, histórico de revisões e opções de exportação, a interface responde bem às necessidades deste perfil.

### Perfil 2 — Marco Rossi

Tendo em conta o perfil de Marco Rossi, cofundador da startup Evo Green Tech, com uma forte componente estratégica e técnica na área das energias renováveis, a proposta de interface vai ao encontro da sua principal preocupação: “Preciso de saber para onde corre o dinheiro antes de decidir o próximo passo da minha empresa."

No separador de Desembolsos, o calendário com filtros como “Pagos”, “Próximo” e “Planeados” permite visualizar de forma simples e organizada as datas previstas de financiamento. Esta funcionalidade permite encontrar de forma rápida e simples as datas de desembolso previstas, e consequentemente, obter visualizações claras de investimento. 

Ainda no mesmo separador, o gráfico de barras horizontal, com possibilidade de filtragem por pilar, permite analisar os investimentos por país de forma comparável. Em vez de olhar apenas para valores globais, o Marco consegue perceber quais os países que estão efetivamente a apostar mais em cada pilar, tornando a análise mais equilibrada e útil para decisões estratégicas. 

Além disso, todos os dados podem ser exportados em PNG, SVG e Excel, uma funcionalidade essencial para integrar a informação em apresentações de pitch dirigidas a investidores.

Por fim, é disponibilizado o separador Pilares, que oferece a possibilidade de explorar cada pilar individualmente e perceber quais as áreas internas que concentram maior investimento. Esta funcionalidade responde diretamente à necessidade de entender onde faz mais sentido expandir a empresa. Em vez de uma visão genérica, o Marco passa a ter uma leitura mais detalhada e orientada para a tomada de decisão.

Concluindo, a interface apresenta a informação de forma clara e acessível, permitindo o Marco compreender rapidamente onde os investimentos estão a ser direcionados. Com visualizações detalhadas, filtros intuitivos e exportação de dados, facilitando a tomada de decisões estratégicas e orientadas para oportunidades reais de crescimento.

### Perfil 3 — Carla Mendes

Tendo em conta o perfil de Carla Mendes, professora do ensino secundário que prefere factsheets, infográficos e representações visuais, especialmente com dados relacionados com educação e comparações entre países, a estrutura do site responde bem às suas necessidades. 
Carla refere frequentemente: “Ouço falar de milhões todos os dias na televisão, mas gostava de ver de forma simples onde é que esse dinheiro está realmente a ser aplicado e quantas pessoas ajudou.”

No menu inicial é possível visualizar um mapa da União Europeia que permite comparar facilmente os diferentes países. Por exemplo, na secção “Distribuição dos fundos do RRF por país”, surge um card que informa o utilizador de que pode clicar num país para obter mais detalhes. Este tipo de indicação ajuda utilizadores menos familiarizados com a navegação digital, oferecendo orientações simples e imediatas sobre como interagir com a plataforma.

No separador “Países”, ao clicar sobre um país, é possível encontrar várias informações sobre esse país, incluindo dados relacionados com o contexto educativo e com as escolas. Esta secção inclui um infográfico que apresenta indicadores de impacto na vida das pessoas, bem como um card especial que emite uma espécie de alerta ao comparar os dados com os restantes países da União Europeia, permitindo verificar se se trata de um problema local ou generalizado. Esta informação revela-se particularmente relevante para o seu contexto profissional.

Por fim, no separador “Marcos e Metas”, é possível observar as promessas associadas aos projetos de cada país, bem como o seu progresso, atrasos e estado de cumprimento. Esta secção permite ainda fazer comparações entre países da União Europeia relativamente ao cumprimento das medidas, algo que Carla definiu como uma necessidade. Esta funcionalidade responde diretamente ao seu interesse em acompanhar o impacto real, a evolução dos investimentos e a comparação entre países.

Em conclusão, o site apresenta uma estrutura intuitiva e de fácil navegação, com dados organizados de forma clara através de pequenos cards informativos, infográficos e outros elementos visuais que facilitam a compreensão da informação. Este tipo de apresentação permite uma leitura rápida e uma interpretação simples dos dados, sendo particularmente eficaz para utilizadores como Carla Mendes, que valorizam representações visuais. Além disso, estas características tornam o site adequado não só para consulta individual, mas também para ser utilizado ou demonstrado em contexto de sala de aula.
