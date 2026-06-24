import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collectors;

public class FBFeedMap {
    private Map<String,List<FBPost>> posts;

    public FBFeedMap(Map<String,List<FBPost>> p) {
        this.setPosts(p);
    }

    public FBFeedMap() {
        this.posts = new HashMap<String,List<FBPost>>();
    }

    public FBFeedMap(FBFeedMap posts) {
        this.posts = posts.getPosts();
    }

    public Map<String,List<FBPost>> getPosts() {
        Map<String,List<FBPost>> novosP = new HashMap<>();

        for (Map.Entry<String,List<FBPost>> entry : this.posts.entrySet()) {
            novosP.put(entry.getKey(),   
                       entry.getValue().stream().map(FBPost :: clone).collect(Collectors.toList())
                     );
        }

        return novosP;
    }

    public void setPosts (Map<String,List<FBPost>> posts) {
        Map<String,List<FBPost>> novosP = new HashMap<>();

        for (Map.Entry<String,List<FBPost>> entry : posts.entrySet()) {
            novosP.put(entry.getKey(),
                       entry.getValue().stream().map(FBPost :: clone).collect(Collectors.toList())
            );
        }

        this.posts = novosP;
    }

    public FBFeedMap clone() {
        return new FBFeedMap(this);
    }

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass()))
            return false;

        FBFeedMap f = (FBFeedMap) o;
        return (f.getPosts().equals(this.posts));
    }

    public void addPost(String user,FBPost post) {
        List<FBPost> lPosts = this.posts.get(user);

        if (lPosts == null) {
            lPosts = new ArrayList<>();
            this.posts.put(user, lPosts);
        }

        lPosts.add(post.clone());
    }

    public void removePosts (String user,LocalDateTime di,LocalDateTime df) {
        List<FBPost> lPosts = this.posts.get(user);

        if (lPosts != null) {
            lPosts.stream().filter(p -> !(p.getTime().isAfter(di) && p.getTime().isBefore(df)))
                        .collect(Collectors.toList());
        }
    }

    public int postsNumPeriodo(LocalDateTime di,LocalDateTime df) {
        int count = 0;

        for (List<FBPost> posts : this.posts.values()) {
            long numPosts = posts.stream().filter(p -> p.getTime().isAfter(di) && p.getTime().isBefore(df))
                                          .count();
        
            count += numPosts;
        }

        return count;
    }

    public String utilizadorMaisActivo(LocalDateTime di,LocalDateTime df) {
        long maxCount = 0;
        String userMax = null;

        for (Map.Entry<String,List<FBPost>> entry : this.posts.entrySet()) {
            long numPosts = entry.getValue().stream()
                                            .filter(post -> post.getTime().isAfter(di) && post.getTime().isBefore(df))
                                            .count();


            if (numPosts > maxCount) {
                maxCount = numPosts;
                userMax = entry.getKey();
            }
        }

        return userMax;
    }

    public List<FBPost> timelineGlobal() {
        List<FBPost> allPosts = new ArrayList<>();

        for (List<FBPost> posts : this.posts.values()) {
            allPosts.addAll(posts.stream().map(FBPost :: clone).collect(Collectors.toList()));
        }

        return allPosts.stream().sorted(new ComparadorPostsTime()).collect(Collectors.toList());
    }
                         

    public boolean validaPostsSimultaneos() {

        for (Map.Entry<String,List<FBPost>> entry : this.posts.entrySet()) {
            Set<LocalDateTime> times = new HashSet<>();

            for (FBPost post : entry.getValue()) {
                if (times.contains(post.getTime())) return false;
                else times.add(post.getTime());
            }
        }

        return true;
    }


}
