import java.time.LocalDate;
import java.util.*;
import java.util.stream.Collectors;

public class SistemaVideos implements Comparable<SistemaVideos> {
    Map<String,Video> videos;

    public SistemaVideos(Map<String,Video> vds) {
        this.setVideos(vds);
    }

    public SistemaVideos() {
        this.videos = new HashMap<String,Video>();
    }

    public SistemaVideos(SistemaVideos sv) {
        this.videos = sv.getVideos();
    }

    public Map<String,Video> getVideos() {
        return this.videos.entrySet()
                          .stream()
                          .collect(Collectors.toMap(e->e.getKey(), e-> e.getValue().clone()));
    }

    public void setVideos(Map<String,Video> videos) {
        Map<String,Video> vds = new HashMap<String,Video>();

        for (Map.Entry<String,Video> vs : videos.entrySet()) {
            vds.put(vs.getKey(),vs.getValue().clone());
        }

        this.videos = vds;
    }   

    public void addVideo(Video v) {
        this.videos.put(v.getNome(),v.clone());
    }

    public Video getVideo(String codVideo) {
        return this.videos.get(codVideo).clone();
    }

    public void removeVideo(String codVideo) {
        this.videos.remove(codVideo);
    }

    public void addLike(String codVideo) {
        Video v = this.videos.get(codVideo);
        v.setLikes(v.getLikes() + 1);
    }

    public String topLikes_v2() {
        return this.videos.keySet()
                          .stream()
                          .sorted((s1,s2) -> this.videos.get(s2).getLikes() - this.videos.get(s1).getLikes())
                          .findFirst()
                          .orElse(null);
    }

    public String topLikes() {
        int maxLikes = Integer.MIN_VALUE;
        String maxCod = null;
        Set<String> vds = this.videos.keySet();

        for (String v : vds) {
            int likesVideo = this.videos.get(v).getLikes();

            if (likesVideo > maxLikes) {
                maxLikes = likesVideo;
                maxCod = v;
            }
        }

        return maxCod;
    }


    public String topLikes(LocalDate dinicial,LocalDate dfinal) {
        int maxLikes = Integer.MIN_VALUE;
        String maxCod = null;
        Set<String> vds = this.videos.keySet();

        for (String v : vds) {
            LocalDate data = this.videos.get(v).getDataLoad().toLocalDate();

            if ((data.isEqual(dinicial) || data.isAfter(dinicial)) && 
                (data.isEqual(dfinal) || data.isBefore(dfinal))) {

                    int likesVideo = this.videos.get(v).getLikes();

                    if (likesVideo > maxLikes) {
                        maxLikes = likesVideo;
                        maxCod = v;
                    }
            }

        }

        return maxCod;
    }

    public String topLikes_v2(LocalDate dinicial,LocalDate dfinal) {
        return this.videos.keySet()
                          .stream()
                          .filter(s -> {
                                LocalDate data = this.videos.get(s).getDataLoad().toLocalDate();
                                return data.isAfter(dinicial) && data.isBefore(dfinal);
                           })
                          .max(Comparator.comparingInt(s -> this.videos.get(s).getLikes()))
                          .orElse(null);  
    }

    public Video videoMaisLongo() {
        Collection<Video> videos = this.videos.values();
        Video maisLongo = null;

        for (Video v : videos) {
            int duracao = v.getDuracaoTotalSeg();            

            if (maisLongo == null || (duracao > maisLongo.getDuracaoTotalSeg())) 
                maisLongo = v.clone();
            
        }

        return maisLongo;
    }

    public Video videoMaisLongo_v2() {
        return this.videos.values()
                          .stream()
                          .max(Comparator.comparingDouble(Video :: getDuracaoTotalSeg))
                          .orElse(null);
    }

    public SistemaVideos clone() {
        return new SistemaVideos(this);
    }

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        SistemaVideos sv = (SistemaVideos) o;
        return sv.getVideos().equals(this.videos);
    }

    public String toString() {
        String out = "";

        for (Map.Entry<String,Video> v : this.videos.entrySet()) {
            out += v.getKey() + " -> " + v.getValue().toString() + "\n";
        }

        return out;
    }


    @Override 
    public int compareTo(SistemaVideos sv1) {
        return this.videos.size() - sv1.getVideos().size();
    }

}
