import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Iterator;
import java.util.List;


public class FBFeed {
    private List<FBPost> posts;

    public FBFeed(List<FBPost> p) {
        this.setPosts(p);
    }

    public FBFeed() {
        this.posts = new ArrayList<>();
    }

    public FBFeed (FBFeed umFeed) {
        this.posts = umFeed.getPosts();
    }

    public ArrayList<FBPost> getPosts() {
        ArrayList<FBPost> novosPosts = new ArrayList<>(posts.size());

        for (FBPost post : this.posts) {
            novosPosts.add(post.clone());
        }

        return novosPosts;
    }

    public void setPosts(List<FBPost> posts) {
        ArrayList<FBPost> novosPosts = new ArrayList<>(posts.size());

        for (FBPost post : posts) {
            novosPosts.add(post.clone());
        }

        this.posts = novosPosts;
    }

    public int nrPosts(String user) {
        int count = 0;

        for (FBPost post : this.posts) {
            if (post.getNome().equals(user))
                count++;
        }

        return count;
    }

    public List<FBPost> postsOf(String user) {
        ArrayList<FBPost> postsUser = new ArrayList<>();

        this.posts.forEach(post -> {
            if (post.getNome().equals(user)) postsUser.add(post);}

        );
    
        return postsUser;
    }

    public List<FBPost> postsOf(String user, LocalDateTime inicio,LocalDateTime fim) {
        ArrayList<FBPost> postsUser = new ArrayList<>();

        this.posts.forEach(post -> {
            if (post.getNome().equals(user) && post.getTime().isAfter(inicio)
                && post.getTime().isBefore(fim)) postsUser.add(post);}
        );
    
        return postsUser;
    }

    public FBPost getPost (int id) {
        boolean encontrou = false;
        Iterator<FBPost> it = this.posts.iterator();
        FBPost post = null;

        while (it.hasNext() && !encontrou) {
            post = it.next();

            if (post.getId() == id) 
                encontrou = true;
        }

        if (!encontrou) return null;
        return post;
    }

    public void comment (int postid,String comentario) {
        boolean adicionado = false;
        Iterator<FBPost> it = this.posts.iterator();

        while (it.hasNext() && !adicionado) {
            FBPost p = it.next();

            if (p.getId() == postid) {
                p.addComentario(comentario);
                adicionado = true;
            }
        }
    }

    public FBPost ordenarPorOrdemAlfabetica() {
        Comparator<FBPost> c = (p1,p2) -> p1.getNome().compareTo(p2.getNome());

        return this.posts.stream().sorted(c)
                         .map(FBPost :: clone)
                         .findFirst()
                         .orElse(null);
    }

    public void comment (FBPost post,String comentario) {
        this.comment(post.getId(), comentario);   
    }

    public void like (int postid) {
        boolean find = false;
        Iterator<FBPost> it = this.posts.iterator();

        while (it.hasNext() && !find) {
            FBPost p = it.next();

            if (p.getId() == postid) {
                p.setLikes(p.getLikes() + 1);;
                find = true;
            }
        }
    }

    public void like (FBPost post) {
        this.like(post.getId());
    }

    // versão com iterador externo
    public List<Integer> top5Comments() {
        List<Integer> listId = new ArrayList<Integer>(5);
        ArrayList<FBPost> posts = this.getPosts();

        for (int i = 0; i < 5; i++) {
            int maxComments = -1;
            FBPost max = null;

            Iterator<FBPost> it = posts.iterator(); 
            while (it.hasNext()) {
                FBPost p = it.next();
                int numComments = p.getComentarios().size();

                if (maxComments == -1  || numComments > maxComments) {
                    maxComments = numComments;
                    max = p.clone();
                }
            }

            if (max != null) {
                listId.add(max.getId());
                posts.remove(max);
            }
        }
       
        return listId;
    }

    public FBFeed clone() {
        return new FBFeed(this);
    }

    public String toString() {
        String out = "";

        for (FBPost fb : this.posts) {
            out += (fb.toString() + "\n");
        }

        return out;
    }

    public boolean equals(Object o) {
        if (o == this)
            return true;

        if ((o == null) || (o.getClass() != this.getClass())) 
            return false;

        FBFeed fd = (FBFeed) o;
        return fd.getPosts().equals(this.posts);
    }
}
